/********************************************************************************
** Form generated from reading ui file 'nanoanalyzer.ui'
**
** Created: Sun Nov 3 15:38:26 2013
**      by: Qt User Interface Compiler version 4.4.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_NANOANALYZER_H
#define UI_NANOANALYZER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <glwidget.h>

QT_BEGIN_NAMESPACE

class Ui_NanoAnalyzerClass
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    GLWidget *widget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;
    QTableView *tableView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NanoAnalyzerClass)
    {
    if (NanoAnalyzerClass->objectName().isEmpty())
        NanoAnalyzerClass->setObjectName(QString::fromUtf8("NanoAnalyzerClass"));
    NanoAnalyzerClass->setWindowModality(Qt::ApplicationModal);
    NanoAnalyzerClass->resize(800, 600);
    centralwidget = new QWidget(NanoAnalyzerClass);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    verticalLayout_2 = new QVBoxLayout(centralwidget);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    widget = new GLWidget(centralwidget);
    widget->setObjectName(QString::fromUtf8("widget"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
    widget->setSizePolicy(sizePolicy);

    horizontalLayout->addWidget(widget);

    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer);

    pushButton = new QPushButton(centralwidget);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    verticalLayout->addWidget(pushButton);


    horizontalLayout->addLayout(verticalLayout);


    verticalLayout_2->addLayout(horizontalLayout);

    tableView = new QTableView(centralwidget);
    tableView->setObjectName(QString::fromUtf8("tableView"));

    verticalLayout_2->addWidget(tableView);

    NanoAnalyzerClass->setCentralWidget(centralwidget);
    menubar = new QMenuBar(NanoAnalyzerClass);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 800, 22));
    NanoAnalyzerClass->setMenuBar(menubar);
    statusbar = new QStatusBar(NanoAnalyzerClass);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    NanoAnalyzerClass->setStatusBar(statusbar);

    retranslateUi(NanoAnalyzerClass);

    QMetaObject::connectSlotsByName(NanoAnalyzerClass);
    } // setupUi

    void retranslateUi(QMainWindow *NanoAnalyzerClass)
    {
    NanoAnalyzerClass->setWindowTitle(QApplication::translate("NanoAnalyzerClass", "NanoAnalyzer", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("NanoAnalyzerClass", "Quit", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(NanoAnalyzerClass);
    } // retranslateUi

};

namespace Ui {
    class NanoAnalyzerClass: public Ui_NanoAnalyzerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NANOANALYZER_H
