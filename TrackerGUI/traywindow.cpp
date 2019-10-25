#include "traywindow.h"

#ifndef QT_NO_SYSTEMTRAYICON

#include <QAction>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QVBoxLayout>

TrayWindow::TrayWindow(QDialog *parent) : QDialog(parent)
{
    createActions();
    createTrayIcon();

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QIcon icon = QIcon("./images/test.png");
    trayIcon->setIcon(icon);
    trayIcon->show();
    trayIcon->setVisible(1);

    setWindowIcon(icon);
    
    //setLayout(mainLayout);
    ui.setupUi(this);

    setWindowTitle(tr("Process Tracker"));
    resize(720, 480);
}

void TrayWindow::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);

    showAction = new QAction(tr("&Show"), this);
    connect(showAction, &QAction::triggered, this, &QWidget::showNormal);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void TrayWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(showAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}

void TrayWindow::closeEvent(QCloseEvent *event)
{
#ifdef Q_OS_OSX
    if (!event->spontaneous() || !isVisible()) {
        return;
    }
#endif
    hide();
    event->ignore();
}

#endif