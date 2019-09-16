extern crate chrono;
extern crate rusqlite;

use rusqlite::types::ToSql;
use rusqlite::{params, Connection, Result};

use chrono::prelude::*;

struct ProcessEntry{
    name:String,
    time_from:String,
    time_to:String,
}

pub fn add_new_entry(conn : &Connection, p_name : String, from : DateTime<Local>, to : DateTime<Local>) -> Result<()>{
    let entry = ProcessEntry {name : p_name, time_from : from.to_string(), time_to : to.to_string()};
    conn.execute("INSERT INTO processes (name, timefrom, timeto) VALUES (?1, ?2, ?3)",
                &[&entry.name, &entry.time_from, &entry.time_to],).unwrap();
    Ok(())
}