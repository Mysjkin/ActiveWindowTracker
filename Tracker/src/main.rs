
mod Tracker;

/*mod DB_debug{
    pub mod access;
}*/
extern crate rusqlite;

use rusqlite::{Connection, Result};

fn init_db(db_name : String) -> Result<Connection>{
    let conn = Connection::open(db_name);
    conn
}

fn main() {
    println!("Tracking...");
    let conn = init_db("tracker.db".to_string()).unwrap();
    /*let res1 = DB_debug::access::update(&conn).unwrap();
    let res = DB_debug::access::get_aggr_data(&conn).unwrap();
    for p in res{
        println!("{:?} {:?}", p.0, p.1);
    }*/
    Tracker::track_active_windows(&conn);
}