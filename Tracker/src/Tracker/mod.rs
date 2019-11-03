
extern crate libxdo_sys;
extern crate libc;
extern crate sysinfo;
extern crate chrono;
extern crate rusqlite;

use chrono::prelude::*;
use chrono::Duration;
use rusqlite::Connection;

mod db_access;

use libxdo_sys::*;
use std::mem;
use std::thread;
use std::ptr::null;
use libc::c_char;
use std::slice::from_raw_parts_mut;
use std::str::from_utf8;
use sysinfo::{System, SystemExt, Process, ProcessExt};

// Checks if mouse has moved since last poll.
// Returns a tuple (has_moved, x, y) : (bool, int, int).
fn poll_mouse_movement(xdo : *const Struct_xdo, curr_x : i32, curr_y : i32) -> (bool, i32, i32) {
    let mut new_x = 0;
    let mut new_y = 0;
    let mut scr_nr = 0;
    unsafe {
        if xdo_get_mouse_location(xdo, &mut new_x, &mut new_y, &mut scr_nr) != 0{
            panic!("Could not get mouse location");
        }   
    }
    if new_x == curr_x && new_y == curr_y{
        return (false, new_x, new_y);
    }
    (true, new_x, new_y)
}

fn pause_until_movement(xdo : *const Struct_xdo, curr_x : i32, curr_y : i32){
    let mut is_afk = true;
    let quater_sec = std::time::Duration::from_secs(1);
    while is_afk{
        let (ret_has_moved, ret_x, ret_y) = poll_mouse_movement(xdo, curr_x, curr_y);
        if ret_has_moved{
            is_afk = false;
            return;
        }
        thread::sleep(quater_sec);
    }
}

fn get_process_name(xdo : *const Struct_xdo) -> String{
    let start_time = Local::now();
    let ret_name;
    unsafe{
        let mut sys = System::new();
        let act_win: *mut u64 = libc::malloc(mem::size_of::<u64>()) as *mut u64;
        sys.refresh_all();
        let mut tries = 1;
        // xdo_get_active_window takes alot of time.
        let mut get_window_result = xdo_get_active_window(xdo, act_win);
        let sleep_before_attempts = std::time::Duration::from_millis(50);
        let tries_before_panic = 5;
        while get_window_result != 0{
            if tries == tries_before_panic{
                panic!("Failed to get active window");
            }
            get_window_result = xdo_get_active_window(xdo, act_win);
            tries += 1;
            if get_window_result != 0{
                thread::sleep(sleep_before_attempts);
            }
        }
        let mut win_name: *mut u8 = libc::malloc(mem::size_of::<u8>()) as *mut u8;
        let mut name_len : i32 = 0;
        let mut name_type : i32 = 0;

        let act_win_pid : i32 = xdo_get_pid_window(xdo, *act_win);
        
        match sys.get_process(act_win_pid) {
            Some(p) => {
                ret_name = Process::name(&p);
            },
            None => panic!("Cannot find process matching pid {:?}", act_win_pid) 
        };

        libc::free(win_name as *mut libc::c_void);
        libc::free(act_win as *mut libc::c_void);
        ret_name.to_string()
    }
}

fn update_db_debug(conn : &Connection, process_name : String, timefrom : DateTime<Local>, timeto : DateTime<Local>){
    println!("entry added: {}, {}, {}", process_name, timefrom, timeto);
}

pub fn track_active_windows(conn : &Connection){
    let mut time_since_active = Local::now();
    let xdo;
    unsafe{
        xdo = xdo_new(null());
        if xdo.is_null() {
            panic!("Failed to init libxdo.");
        }
    }
    let mut curr_x = 0;
    let mut curr_y = 0;
    let mut has_moved = true;
    let mut process_start_time = Local::now();
    let mut pname = "-1".to_string();
    // xdo_get_active_window is slow find better fix later.
    let collection_granularity = std::time::Duration::from_secs(10);
    while true{
        let (ret_has_moved, ret_x, ret_y) = poll_mouse_movement(xdo, curr_x, curr_y);
        has_moved = ret_has_moved; 
        curr_x = ret_x; 
        curr_y = ret_y;
        if has_moved == true{
            time_since_active = Local::now();
        }
        else{
            let afk_time = Local::now() - time_since_active;
            if afk_time > Duration::minutes(3){
                pause_until_movement(xdo, curr_x, curr_y);
                time_since_active = Local::now();
            }
        }
        if has_moved{
            let new_pname = get_process_name(xdo);
            if pname == "-1"{
                pname = new_pname.to_string();
            }
            else if pname != new_pname {
                db_access::add_new_entry(&conn, pname.to_string(), process_start_time, Local::now());
                pname = new_pname.to_string();
                process_start_time = Local::now();
            }
        }
        if Local::now() - process_start_time > Duration::seconds(120){
            db_access::add_new_entry(&conn, pname.to_string(), process_start_time, Local::now());
            process_start_time = Local::now();
        }
        let process_duration = Local::now() - process_start_time;

        thread::sleep(collection_granularity);
    }
}