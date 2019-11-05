#ifndef TRAYWINDOW_H
#define TRAYWINDOW_H

#include <QSystemTrayIcon>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QDialog>
#include <QtWidgets>
#include <QAction>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QVBoxLayout>
#include "dbaccess.h"

#include <iostream>

#include <QtSql>

#include "ui_traywindow.h"

class QAction;
class QLabel;
class QPushButton;

class TrayWindow : public QDialog
{
    Q_OBJECT

public:
    TrayWindow(QDialog *parent = nullptr);

public slots:
    void onClickedUpdate();

private:
    void createActions();
    void createTrayIcon();

    DbAccess* db;
    QLabel *iconLabel;
    Ui::TrayWindow ui;
    QSqlRelationalTableModel *model;

    QAction *minimizeAction;
    QAction *showAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
};

#endif // QT_NO_SYSTEMTRAYICON

#endif
