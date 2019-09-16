#include <QApplication>

#include <QMessageBox>
#include "traywindow.h"

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
    //window.show();
    return app.exec();
}
