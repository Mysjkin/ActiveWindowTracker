
#ifndef DBACCESS_H
#define DBACCESS_H

#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QString>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <utility>

#include <iostream>

struct Duration
{
    std::string name;
    std::string lastUpdated;
    int duration;
    std::string category;
};

class DbAccess
{
private:
    std::string driverType;
    std::string dbName;
    QSqlDatabase db;
public:
    DbAccess(std::string dbName, std::string driverType);

    bool init();

    void updateDurations();

    void updateCategory(std::vector<std::pair<int, std::string>> categoryPairs);

    std::vector<Duration> getAllDurations();

    ~DbAccess();
};

#endif
