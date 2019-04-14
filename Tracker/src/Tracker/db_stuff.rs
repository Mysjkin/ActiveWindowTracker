

extern crate chrono;
extern crate rusqlite;

use rusqlite::{Connection, Result};
use chrono::{DateTime, NaiveDateTime, Utc};

struct ProcessEntry{
    name:String,
    time_from:DateTime<Utc>,
    time_to:DateTime<Utc>
}


/*
let conn = Connection::open("cats.db");

*/