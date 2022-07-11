/********************************************************************************
** Form generated from reading UI file 'Lab10Qt.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB10QT_H
#define UI_LAB10QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lab10QtClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lab10QtClass)
    {
        if (Lab10QtClass->objectName().isEmpty())
            Lab10QtClass->setObjectName(QString::fromUtf8("Lab10QtClass"));
        Lab10QtClass->resize(600, 400);
        menuBar = new QMenuBar(Lab10QtClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Lab10QtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lab10QtClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Lab10QtClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Lab10QtClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Lab10QtClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Lab10QtClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Lab10QtClass->setStatusBar(statusBar);

        retranslateUi(Lab10QtClass);

        QMetaObject::connectSlotsByName(Lab10QtClass);
    } // setupUi

    void retranslateUi(QMainWindow *Lab10QtClass)
    {
        Lab10QtClass->setWindowTitle(QCoreApplication::translate("Lab10QtClass", "Lab10Qt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lab10QtClass: public Ui_Lab10QtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB10QT_H
