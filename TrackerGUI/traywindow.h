#ifndef TRAYWINDOW_H
#define TRAYWINDOW_H

#include <QSystemTrayIcon>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QDialog>
#include <QtWidgets>

#include "ui_traywindow.h"

class QAction;
class QLabel;
class QPushButton;

class TrayWindow : public QDialog
{
    Q_OBJECT

public:
    TrayWindow(QDialog *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void createActions();
    void createTrayIcon();

    QLabel *iconLabel;
    Ui::TrayWindow ui;

    QAction *minimizeAction;
    QAction *showAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
};

#endif // QT_NO_SYSTEMTRAYICON

#endif
