/********************************************************************************
** Form generated from reading ui file 'nanoanalyzer.ui'
**
** Created: Fri Nov 8 18:07:22 2013
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
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_NanoAnalyzerClass
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    GLWidget *modelView;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QLabel *label_4;
    QLineEdit *v;
    QLabel *label_3;
    QLineEdit *dy;
    QLabel *label_2;
    QLineEdit *dx;
    QLabel *label;
    QLineEdit *rowPointsCount;
    QPushButton *startButton;
    QTableView *tableView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NanoAnalyzerClass)
    {
    if (NanoAnalyzerClass->objectName().isEmpty())
        NanoAnalyzerClass->setObjectName(QString::fromUtf8("NanoAnalyzerClass"));
    NanoAnalyzerClass->setWindowModality(Qt::ApplicationModal);
    NanoAnalyzerClass->resize(1096, 953);
    centralwidget = new QWidget(NanoAnalyzerClass);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    verticalLayout = new QVBoxLayout(centralwidget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    splitter = new QSplitter(centralwidget);
    splitter->setObjectName(QString::fromUtf8("splitter"));
    splitter->setOrientation(Qt::Vertical);
    widget = new QWidget(splitter);
    widget->setObjectName(QString::fromUtf8("widget"));
    verticalLayout_3 = new QVBoxLayout(widget);
    verticalLayout_3->setMargin(0);
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(0);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    modelView = new GLWidget(widget);
    modelView->setObjectName(QString::fromUtf8("modelView"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(modelView->sizePolicy().hasHeightForWidth());
    modelView->setSizePolicy(sizePolicy);

    horizontalLayout->addWidget(modelView);

    verticalLayout_2 = new QVBoxLayout();
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    verticalLayout_2->setContentsMargins(10, -1, 0, -1);
    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_2->addItem(verticalSpacer);

    label_4 = new QLabel(widget);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    verticalLayout_2->addWidget(label_4);

    v = new QLineEdit(widget);
    v->setObjectName(QString::fromUtf8("v"));
    v->setEnabled(false);
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(v->sizePolicy().hasHeightForWidth());
    v->setSizePolicy(sizePolicy1);

    verticalLayout_2->addWidget(v);

    label_3 = new QLabel(widget);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    verticalLayout_2->addWidget(label_3);

    dy = new QLineEdit(widget);
    dy->setObjectName(QString::fromUtf8("dy"));
    QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(dy->sizePolicy().hasHeightForWidth());
    dy->setSizePolicy(sizePolicy2);

    verticalLayout_2->addWidget(dy);

    label_2 = new QLabel(widget);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    verticalLayout_2->addWidget(label_2);

    dx = new QLineEdit(widget);
    dx->setObjectName(QString::fromUtf8("dx"));
    sizePolicy1.setHeightForWidth(dx->sizePolicy().hasHeightForWidth());
    dx->setSizePolicy(sizePolicy1);

    verticalLayout_2->addWidget(dx);

    label = new QLabel(widget);
    label->setObjectName(QString::fromUtf8("label"));

    verticalLayout_2->addWidget(label);

    rowPointsCount = new QLineEdit(widget);
    rowPointsCount->setObjectName(QString::fromUtf8("rowPointsCount"));
    sizePolicy1.setHeightForWidth(rowPointsCount->sizePolicy().hasHeightForWidth());
    rowPointsCount->setSizePolicy(sizePolicy1);

    verticalLayout_2->addWidget(rowPointsCount);

    startButton = new QPushButton(widget);
    startButton->setObjectName(QString::fromUtf8("startButton"));

    verticalLayout_2->addWidget(startButton);


    horizontalLayout->addLayout(verticalLayout_2);


    verticalLayout_3->addLayout(horizontalLayout);

    splitter->addWidget(widget);
    tableView = new QTableView(splitter);
    tableView->setObjectName(QString::fromUtf8("tableView"));
    splitter->addWidget(tableView);

    verticalLayout->addWidget(splitter);

    NanoAnalyzerClass->setCentralWidget(centralwidget);
    menubar = new QMenuBar(NanoAnalyzerClass);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 1096, 22));
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
    label_4->setText(QApplication::translate("NanoAnalyzerClass", "V(nm*2):", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("NanoAnalyzerClass", "dX(nm):", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("NanoAnalyzerClass", "dY(nm):", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("NanoAnalyzerClass", "Step:", 0, QApplication::UnicodeUTF8));
    rowPointsCount->setInputMask(QString());
    startButton->setText(QApplication::translate("NanoAnalyzerClass", "PushButton", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(NanoAnalyzerClass);
    } // retranslateUi

};

namespace Ui {
    class NanoAnalyzerClass: public Ui_NanoAnalyzerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NANOANALYZER_H
