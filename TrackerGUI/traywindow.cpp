#include "traywindow.h"

#ifndef QT_NO_SYSTEMTRAYICON

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
    
    ui.setupUi(this);

    setWindowTitle(tr("Process Tracker"));
    resize(720, 480);
    
    DbAccess* db = new DbAccess("tracker.db", "QSQLITE");

    if(!db->init())
        QMessageBox::critical(this, "Unable to load database", "Unable to open the database");

    model = new QSqlRelationalTableModel(ui.durationTable);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("durations");

    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, tr("Process name"));
    model->setHeaderData(model->fieldIndex("lastupdated"), Qt::Horizontal, tr("Last updated"));
    model->setHeaderData(model->fieldIndex("duration"), Qt::Horizontal, tr("Duration"));
    model->setHeaderData(model->fieldIndex("category"), Qt::Horizontal, tr("Category"));
    
    if (!model->select()){
        QMessageBox::critical(this, "Unable to load database", model->lastError().text());
        return;
    }

    ui.durationTable->setModel(model);
    ui.durationTable->setColumnHidden(model->fieldIndex("id"), true);
    ui.durationTable->setSelectionMode(QAbstractItemView::SingleSelection);

    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(ui.categoryEdit, model->fieldIndex("category"));

    connect(ui.durationTable->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            mapper,
            &QDataWidgetMapper::setCurrentModelIndex);
    ui.durationTable->setCurrentIndex(model->index(0,0));
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

#endif