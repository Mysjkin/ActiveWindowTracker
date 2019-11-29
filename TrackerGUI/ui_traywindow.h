/********************************************************************************
** Form generated from reading UI file 'traywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRAYWINDOW_H
#define UI_TRAYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrayWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *vboxLayout;
    QGroupBox *groupBox;
    QVBoxLayout *vboxLayout1;
    QTableView *durationTable;
    QGroupBox *groupBox_1;
    QFormLayout *formLayout;
    QLabel *label_1;
    QLineEdit *categoryEdit;
    QPushButton *bntUpdateAll;
    QGraphicsView *graphicsView;

    void setupUi(QDialog *TrayWindow)
    {
        if (TrayWindow->objectName().isEmpty())
            TrayWindow->setObjectName(QStringLiteral("TrayWindow"));
        TrayWindow->resize(900, 438);
        centralWidget = new QWidget(TrayWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setGeometry(QRect(0, 0, 481, 411));
        vboxLayout = new QVBoxLayout(centralWidget);
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        vboxLayout->setContentsMargins(9, 9, 9, 9);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        vboxLayout1 = new QVBoxLayout(groupBox);
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        vboxLayout1->setContentsMargins(9, 9, 9, 9);
        durationTable = new QTableView(groupBox);
        durationTable->setObjectName(QStringLiteral("durationTable"));
        durationTable->setSelectionBehavior(QAbstractItemView::SelectRows);

        vboxLayout1->addWidget(durationTable);

        groupBox_1 = new QGroupBox(groupBox);
        groupBox_1->setObjectName(QStringLiteral("groupBox_1"));
        formLayout = new QFormLayout(groupBox_1);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_1 = new QLabel(groupBox_1);
        label_1->setObjectName(QStringLiteral("label_1"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_1);

        categoryEdit = new QLineEdit(groupBox_1);
        categoryEdit->setObjectName(QStringLiteral("categoryEdit"));
        categoryEdit->setEnabled(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, categoryEdit);


        vboxLayout1->addWidget(groupBox_1);

        bntUpdateAll = new QPushButton(groupBox);
        bntUpdateAll->setObjectName(QStringLiteral("bntUpdateAll"));

        vboxLayout1->addWidget(bntUpdateAll);


        vboxLayout->addWidget(groupBox);

        graphicsView = new QGraphicsView(TrayWindow);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(510, 40, 361, 271));

        retranslateUi(TrayWindow);

        QMetaObject::connectSlotsByName(TrayWindow);
    } // setupUi

    void retranslateUi(QDialog *TrayWindow)
    {
        TrayWindow->setWindowTitle(QApplication::translate("TrayWindow", "Tracker UI", Q_NULLPTR));
        groupBox->setTitle(QString());
        groupBox_1->setTitle(QApplication::translate("TrayWindow", "Change Category", Q_NULLPTR));
        label_1->setText(QApplication::translate("TrayWindow", "<b>Category:</b>", Q_NULLPTR));
        bntUpdateAll->setText(QApplication::translate("TrayWindow", "Update All", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TrayWindow: public Ui_TrayWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRAYWINDOW_H
