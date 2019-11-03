
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
    Tracker::track_active_windows(&conn);
}