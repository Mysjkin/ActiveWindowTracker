#include <QApplication>

#include <QMessageBox>
#include "traywindow.h"
#include "dbaccess.h"

#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(systray);

    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(nullptr, QObject::tr("Systray"),
                            QObject::tr("I couldn't detect any system tray "
                                        "on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    TrayWindow window;

    DbAccess* db = new DbAccess("tracker.db", "QSQLITE");
    db->init();
    try{
        db->updateDurations();
        std::vector<Duration> durs = db->getAllDurations();
        for (auto i = durs.begin(); i != durs.end(); ++i){
            std::cout << "Result: " << i->name << " " << i->duration << std::endl;
        }
    }
    catch (const char* msg){
        std::cerr << msg << "\n";
    }
    delete db;

    return app.exec();
}