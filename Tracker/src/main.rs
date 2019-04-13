extern crate libxdo_sys;
extern crate libc;

use libxdo_sys::*;
use std::mem;
use std::ptr::null;
use std::{thread, time};
use libc::c_char;
use std::slice::from_raw_parts_mut;
use std::str::from_utf8;

fn main() {
    let quater_sec = time::Duration::from_millis(250);
    unsafe {
        let xdo = xdo_new(null());

        if xdo.is_null() {
            panic!("Failed to init libxdo.");
        }

        while true{
            let act_win: *mut u64 = libc::malloc(mem::size_of::<u64>()) as *mut u64;

            if xdo_get_active_window(xdo, act_win) != 0 {
                panic!("Failed to get active window");
            }

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

            libc::free(act_win as *mut libc::c_void);
            libc::free(win_name as *mut libc::c_void);
            thread::sleep(quater_sec);
        }

        xdo_free(xdo);
    }
}