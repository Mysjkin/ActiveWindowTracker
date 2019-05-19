
extern crate libxdo_sys;
extern crate libc;
extern crate sysinfo;

use super::DB;

use libxdo_sys::*;
use std::thread;
use std::ptr::null;
use std::time::{Duration, Instant};
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

pub fn track_active_windows(){
    let mut elapsed_mouse_mov = 0;
    let mut time_now = Instant::now();
    let mut is_afk = false;

    unsafe{
        let xdo = xdo_new(null());

        if xdo.is_null() {
            panic!("Failed to init libxdo.");
        }
        let mut curr_x = 0;
        let mut curr_y = 0;
        let mut has_moved = true;
        while true{
            let (ret_has_moved, ret_x, ret_y) = poll_mouse_movement(xdo, curr_x, curr_y);
            has_moved = ret_has_moved; 
            curr_x = ret_x; 
            curr_y = ret_y;
            println!("{}, {}, {}", has_moved, curr_x, curr_y);
            let quater_sec = Duration::from_millis(250);
            thread::sleep(quater_sec);
        }
    }

    /*let quater_sec = Duration::from_millis(250);
    let start = Instant::now();
    thread::sleep(quater_sec);
    let duration = start.elapsed();
    println!("Time elapsed in expensive_function() is: {:?}", duration);

    let conn = Connection::open("cats.db");

    unsafe {
        let mut sys = System::new();
        let xdo = xdo_new(null());

        if xdo.is_null() {
            panic!("Failed to init libxdo.");
        }

        while true{
            let act_win: *mut u64 = libc::malloc(mem::size_of::<u64>()) as *mut u64;
            sys.refresh_all();
            if xdo_get_active_window(xdo, act_win) != 0 {
                //panic!("Failed to get active window");
            }
            else {
                let mut win_name: *mut u8 = libc::malloc(mem::size_of::<u8>()) as *mut u8;
                let mut name_len : i32 = 0;
                let mut name_type : i32 = 0;

                if xdo_get_window_name(xdo, *act_win, &mut win_name, &mut name_len, &mut name_type) != 0{
                    panic!("Failed to get window name");
                }
                else{
                    let slice = from_raw_parts_mut(win_name, name_len as usize);
                    let name = from_utf8(&slice).unwrap();
                    println!("{:?}", name);
                }

                let act_win_pid : i32 = xdo_get_pid_window(xdo, *act_win);
                //let proc_ = sys.get_process(act_win_pid);
                
                match sys.get_process(act_win_pid) {
                    Some(p) => {
                        println!("{:?}, {:?}", act_win_pid, Process::name(&p));
                    },
                    None => panic!("Cannot find process matching pid {:?}", act_win_pid) 
                };

                libc::free(win_name as *mut libc::c_void);
            }
            libc::free(act_win as *mut libc::c_void);
            thread::sleep(quater_sec);
        }

        xdo_free(xdo);
    }
    */
}