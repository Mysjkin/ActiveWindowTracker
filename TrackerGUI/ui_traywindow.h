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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
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

    void setupUi(QDialog *TrayWindow)
    {
        if (TrayWindow->objectName().isEmpty())
            TrayWindow->setObjectName(QStringLiteral("TrayWindow"));
        TrayWindow->resize(601, 420);
        centralWidget = new QWidget(TrayWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        vboxLayout = new QVBoxLayout(centralWidget);
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        vboxLayout->setContentsMargins(9, 9, 9, 9);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        vboxLayout1 = new QVBoxLayout(groupBox);
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));

        vboxLayout->addWidget(groupBox);


        retranslateUi(TrayWindow);

        QMetaObject::connectSlotsByName(TrayWindow);
    } // setupUi

    void retranslateUi(QDialog *TrayWindow)
    {
        TrayWindow->setWindowTitle(QApplication::translate("TrayWindow", "Tracker UI", Q_NULLPTR));
        groupBox->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class TrayWindow: public Ui_TrayWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRAYWINDOW_H
