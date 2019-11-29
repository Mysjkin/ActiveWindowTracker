#include "traywindow.h"

#ifndef QT_NO_SYSTEMTRAYICON

TrayWindow::TrayWindow(QDialog *parent) : QDialog(parent)
{
    createActions();
    createTrayIcon();

    QIcon icon = QIcon("./images/test.png");
    trayIcon->setIcon(icon);
    trayIcon->show();
    trayIcon->setVisible(1);

    setWindowIcon(icon);
    
    ui.setupUi(this);

    setWindowTitle(tr("Process Tracker"));
    resize(900, 480);
    
    db = new DbAccess("tracker.db", "QSQLITE");

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

    connect(ui.bntUpdateAll, SIGNAL(released()), this, SLOT(onClickedUpdate()));
    
    createBarChart();
}

void TrayWindow::testEvent(){
    QMessageBox::critical(this, "Unable to update durations in database", "asd");
}

void TrayWindow::createBarChart(){
    std::vector<Duration> durations = db->getAllDurations();
    std::vector<QBarSet*> sets;
    std::sort(durations.begin(), durations.end(), 
        [](const Duration &a, const Duration &b) -> bool{
            return a.duration > b.duration;
        });

    int index, maxDuration;
    index = maxDuration = 0;
    for (auto d : durations){
        QBarSet *set = new QBarSet(QString::fromStdString(d.name));
        *set << d.duration;
        sets.push_back(set);
        if (maxDuration < d.duration) maxDuration = d.duration;
        if (++index > 2) break;
    }
    std::vector<QBarSeries*> barSeries;
    for (auto s : sets){
        QBarSeries *series = new QBarSeries();
        series->append(s);
        barSeries.push_back(series);
    }

    QChart *chart = new QChart();
    chart->setTitle("Top three most used applications");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,maxDuration + 1);
    chart->addAxis(axisY, Qt::AlignLeft);

    for (auto s : barSeries){
        chart->addSeries(s);
        s->attachAxis(axisY);
    }

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    ui.barChart1->setChart(chart);
    ui.barChart1->setRenderHint(QPainter::Antialiasing);
}

void TrayWindow::onClickedUpdate(){
    try{
        db->updateDurations();
    }
    catch (const char* msg){
        QMessageBox::critical(this, "Unable to update durations in database", msg);
    }
    model->submitAll();
    createBarChart();
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
