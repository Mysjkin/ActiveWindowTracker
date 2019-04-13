extern crate libxdo_sys;
extern crate libc;
extern crate chrono;
extern crate rusqlite;
extern crate sysinfo;
extern crate azul;

use rusqlite::{Connection, Result};
use chrono::{DateTime, NaiveDateTime, Utc};
use std::collections::HashMap;
use libxdo_sys::*;
use std::mem;
use std::ptr::null;
use std::thread;
use std::time::{Duration, Instant};
use libc::c_char;
use std::slice::from_raw_parts_mut;
use std::str::from_utf8;
use sysinfo::{System, SystemExt, Process, ProcessExt};

use azul::{prelude::*, widgets::{label::Label, button::Button}};

struct ProcessEntry{
    name:String,
    time_from:DateTime<Utc>,
    time_to:DateTime<Utc>
}

struct DataModel {
    counter: usize,
}

impl Layout for DataModel {
    fn layout(&self, _info: LayoutInfo<Self>) -> Dom<Self> {
        let label = Label::new(format!("{}", self.counter)).dom();
        let button = Button::with_label("Update counter").dom()
            .with_callback(On::MouseUp, Callback(update_counter));

        Dom::div()
            .with_child(label)
            .with_child(button)
    }
}

fn update_counter(app_state: &mut AppState<DataModel>, _: &mut CallbackInfo<DataModel>) -> UpdateScreen {
    app_state.data.modify(|state| state.counter += 1)?;
    Redraw
}

fn main() {
    let mut app = App::new(DataModel { counter: 0 }, AppConfig::default()).unwrap();
    let window = app.create_window(WindowCreateOptions::default(), css::native()).unwrap();
    app.run(window).unwrap();
}

fn main1() {
    let quater_sec = Duration::from_millis(250);
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
    
}