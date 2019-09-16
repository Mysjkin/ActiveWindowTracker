#ifndef TRAYWINDOW_H
#define TRAYWINDOW_H

#include <QSystemTrayIcon>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QDialog>

class QAction;
class QLabel;
class QPushButton;

class TrayWindow : public QDialog
{
    Q_OBJECT

public:
    TrayWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void createActions();
    void createTrayIcon();

    QLabel *iconLabel;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
};

#endif // QT_NO_SYSTEMTRAYICON

#endif
