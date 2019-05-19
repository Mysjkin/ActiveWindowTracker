
mod Tracker;

mod DB {
    pub mod access;
}

extern crate chrono;
use chrono::prelude::*;
use chrono::Duration;

use Tracker::track_active_windows;

fn main() {
    println!("asd");
    let now = Local::now();
    let now2 = now + Duration::minutes(2);
    let conn = DB::access::init("tracker.db".to_string()).unwrap();
    //DB::access::add_new_entry(&conn, "Firefox".to_string(), now, now2);
    let res = DB::access::get_aggr_data(&conn).unwrap();
    let res1 = DB::access::update(&conn).unwrap();
    for p in res{
        println!("{:?} {:?}", p.0, p.1);
    }
    //track_active_windows();
}