#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QString>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

#include <iostream>

struct duration
{
    int id;
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
    
    std::vector<duration> getAllDurations();

    ~DbAccess();
};