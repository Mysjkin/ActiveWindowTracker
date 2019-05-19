
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

struct Duration{
    name:String,
    duration:f32,
    lastupdate:String,
}

struct AggregatedTimes{
    name:String,
    time_in_secs:i32,
}

// Should be a singleton.
pub fn init(db_name : String) -> Result<Connection>{
    let conn = Connection::open(db_name);
    conn
}
pub fn add_new_entry(conn : &Connection, p_name : String, from : DateTime<Local>, to : DateTime<Local>) -> Result<()>{
    let entry = ProcessEntry {name : p_name, time_from : from.to_string(), time_to : to.to_string()};
    conn.execute("INSERT INTO processes (name, timefrom, timeto) VALUES (?1, ?2, ?3)",
                &[&entry.name, &entry.time_from, &entry.time_to],).unwrap();
    Ok(())
}

pub fn update(conn : &Connection) -> Result<()>{
    let mut stmt = conn.prepare("Select p.name, sum 
                                (Cast((JulianDay(timeto) - JulianDay(timefrom)) * 24 * 60 * 60 As Integer)) 
                                from Processes p
	                            where timefrom < timeto
	                            group by p.name;")?;
    let processes = stmt.query_map(params![], |row| {
        Ok(AggregatedTimes {
            name: row.get(0)?,
            time_in_secs: row.get(1)?,
        })
    })?;
    for distinct_process in processes {
        let p = distinct_process.unwrap();
        conn.execute("INSERT OR REPLACE INTO DURATIONS (id, name, lastupdated, duration)
                        values ((select id from DURATIONS where name=?1), ?1, ?2, ?3);", 
                        &[&p.name, &Local::now().to_string(), &p.time_in_secs.to_string()]).unwrap();
    }

    Ok(())
}

pub fn get_aggr_data(conn : &Connection) -> Result<(Vec<(String, i32)>)>{
    let mut stmt = conn.prepare("Select name, duration from DURATIONS;")?;
    let processes = stmt.query_map(params![], |row| {
        Ok(AggregatedTimes {
            name: row.get(0)?,
            time_in_secs: row.get(1)?,
        })
    })?;
    let mut ret_process = Vec::new();
    for distinct_process in processes {
        let p = distinct_process.unwrap();
        ret_process.push((p.name, p.time_in_secs));
    }
    Ok((ret_process))
}