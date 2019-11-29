
#include "dbaccess.h"

DbAccess::DbAccess(std::string dbName, std::string driverType){
    this->dbName = dbName;
    this->driverType = driverType;
}
DbAccess::~DbAccess(){
    db.close();
}
bool DbAccess::init(){
    db = QSqlDatabase::addDatabase(QString::fromStdString(driverType));
    db.setDatabaseName(QString::fromStdString(dbName));
    return db.open();
}

void DbAccess::updateDurations(){
    QSqlQuery queryGet;
    std::string selectProcAsDur = 
        "Select p.name, sum(Cast((JulianDay(timeto) - JulianDay(timefrom)) * 24 * 60 As Integer)) "
        "from Processes p " 
        "where (timefrom < timeto and (timefrom > (select d.lastupdated from DURATIONS d where d.name == p.name))) "
        "or p.name not in (select d.name from DURATIONS d) "
        "group by p.name;";
    bool prepared = queryGet.prepare(QString::fromStdString(selectProcAsDur));
    if (!prepared){
        throw "Could not prepare" + selectProcAsDur + " sql command";
    }
    if(!queryGet.exec()){
        throw "Could not execute " + selectProcAsDur + " sql command";
    }
    
    std::string insertDurs = 
        "INSERT OR REPLACE INTO DURATIONS (id, name, lastupdated, duration) "
        "values ((select id from DURATIONS where name=:name), :name, :lastupdated, :duration);";
    while(queryGet.next()){
        QSqlQuery queryInsert;
        QString procName = queryGet.value(0).toString();
        int duration = queryGet.value(1).toString().toInt();

        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t tnow = std::chrono::system_clock::to_time_t(now);
        std::string nowStr = std::ctime(&tnow);
        QString nowQStr = QString::fromStdString(nowStr);

        prepared = queryInsert.prepare(QString::fromStdString(insertDurs));
        queryInsert.bindValue(":name", procName);
        queryInsert.bindValue(":lastupdated", nowQStr);
        queryInsert.bindValue(":duration", duration);
        if (!prepared){
            throw "Could not prepare " + insertDurs + " sql command";
        }
        if(!queryInsert.exec()){
            throw "Could not execute " + insertDurs + " sql command";
        }
        queryInsert.clear();
    }
}

std::vector<Duration> DbAccess::getAllDurations(){
    std::vector<Duration> v;
    QSqlQuery queryGet;
    std::string selectDurs = "Select name, lastupdated, duration, category from DURATIONS;";

    bool prepared = queryGet.prepare(QString::fromStdString(selectDurs));
    if (!prepared){
        throw "Could not prepare " + selectDurs + " sql command";
    }
    if (!queryGet.exec()){
        throw "Could not execute " + selectDurs + " sql command";
    }
    
    while(queryGet.next()){
        std::string name = queryGet.value(0).toString().toStdString();
        std::string lastupdated = queryGet.value(1).toString().toStdString();
        int duration = queryGet.value(2).toString().toInt();
        std::string category = queryGet.value(3).toString().toStdString();
        Duration d = {name, lastupdated, duration, category};
        v.push_back(d);
    }   
    return v;
}

void DbAccess::updateCategory(std::vector<std::pair<int, std::string>> categoryPairs){
    QSqlQuery updateCategory;
    std::string updateQuery = "update DURATIONS set category=c where ID=i values (:i, :c);";
    bool prepared = updateCategory.prepare(QString::fromStdString(updateQuery));
    if (!prepared){
        throw "Could not prepare" + updateQuery + " sql command";
    }
    for (auto cp : categoryPairs){
        updateCategory.bindValue(":i", cp.first);
        updateCategory.bindValue(":c", QString::fromStdString(cp.second));
        if (!updateCategory.exec()){
            throw "Could not execute " + updateQuery + " sql command";
        }
    }
}

















