/********************************************************************************
** Form generated from reading ui file 'nanoanalyzer.ui'
**
** Created: Fri Dec 13 14:35:09 2013
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
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
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
    QLabel *label_5;
    QLineEdit *positive_v;
    QLabel *label_4;
    QLineEdit *negative_v;
    QLabel *label_3;
    QLineEdit *dy;
    QLabel *label_2;
    QLineEdit *dx;
    QLabel *label;
    QSpinBox *rowPointsCount;
    QGroupBox *groupBox;
    QRadioButton *points_view;
    QRadioButton *lines_view;
    QRadioButton *shade_view;
    QPushButton *colorButton;
    QGroupBox *groupBox_2;
    QRadioButton *gradientButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *selectFileButton;
    QTableView *tableView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NanoAnalyzerClass)
    {
    if (NanoAnalyzerClass->objectName().isEmpty())
        NanoAnalyzerClass->setObjectName(QString::fromUtf8("NanoAnalyzerClass"));
    NanoAnalyzerClass->setWindowModality(Qt::ApplicationModal);
    NanoAnalyzerClass->resize(1298, 836);
    centralwidget = new QWidget(NanoAnalyzerClass);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    verticalLayout = new QVBoxLayout(centralwidget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    splitter = new QSplitter(centralwidget);
    splitter->setObjectName(QString::fromUtf8("splitter"));
    splitter->setOrientation(Qt::Vertical);
    widget = new QWidget(splitter);
    widget->setObjectName(QString::fromUtf8("widget"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
    widget->setSizePolicy(sizePolicy);
    verticalLayout_3 = new QVBoxLayout(widget);
    verticalLayout_3->setMargin(0);
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(0);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    modelView = new GLWidget(widget);
    modelView->setObjectName(QString::fromUtf8("modelView"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(modelView->sizePolicy().hasHeightForWidth());
    modelView->setSizePolicy(sizePolicy1);

    horizontalLayout->addWidget(modelView);

    verticalLayout_2 = new QVBoxLayout();
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    verticalLayout_2->setContentsMargins(10, -1, 0, -1);
    label_5 = new QLabel(widget);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    verticalLayout_2->addWidget(label_5);

    positive_v = new QLineEdit(widget);
    positive_v->setObjectName(QString::fromUtf8("positive_v"));
    positive_v->setEnabled(false);
    QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(positive_v->sizePolicy().hasHeightForWidth());
    positive_v->setSizePolicy(sizePolicy2);

    verticalLayout_2->addWidget(positive_v);

    label_4 = new QLabel(widget);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    verticalLayout_2->addWidget(label_4);

    negative_v = new QLineEdit(widget);
    negative_v->setObjectName(QString::fromUtf8("negative_v"));
    negative_v->setEnabled(false);
    sizePolicy2.setHeightForWidth(negative_v->sizePolicy().hasHeightForWidth());
    negative_v->setSizePolicy(sizePolicy2);

    verticalLayout_2->addWidget(negative_v);

    label_3 = new QLabel(widget);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    verticalLayout_2->addWidget(label_3);

    dy = new QLineEdit(widget);
    dy->setObjectName(QString::fromUtf8("dy"));
    QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Fixed);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(dy->sizePolicy().hasHeightForWidth());
    dy->setSizePolicy(sizePolicy3);

    verticalLayout_2->addWidget(dy);

    label_2 = new QLabel(widget);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    verticalLayout_2->addWidget(label_2);

    dx = new QLineEdit(widget);
    dx->setObjectName(QString::fromUtf8("dx"));
    sizePolicy2.setHeightForWidth(dx->sizePolicy().hasHeightForWidth());
    dx->setSizePolicy(sizePolicy2);

    verticalLayout_2->addWidget(dx);

    label = new QLabel(widget);
    label->setObjectName(QString::fromUtf8("label"));

    verticalLayout_2->addWidget(label);

    rowPointsCount = new QSpinBox(widget);
    rowPointsCount->setObjectName(QString::fromUtf8("rowPointsCount"));
    rowPointsCount->setMinimum(1);
    rowPointsCount->setMaximum(999);
    rowPointsCount->setValue(84);

    verticalLayout_2->addWidget(rowPointsCount);

    groupBox = new QGroupBox(widget);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(6);
    sizePolicy4.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
    groupBox->setSizePolicy(sizePolicy4);
    groupBox->setMinimumSize(QSize(0, 101));
    points_view = new QRadioButton(groupBox);
    points_view->setObjectName(QString::fromUtf8("points_view"));
    points_view->setGeometry(QRect(10, 10, 84, 18));
    lines_view = new QRadioButton(groupBox);
    lines_view->setObjectName(QString::fromUtf8("lines_view"));
    lines_view->setGeometry(QRect(10, 30, 84, 18));
    shade_view = new QRadioButton(groupBox);
    shade_view->setObjectName(QString::fromUtf8("shade_view"));
    shade_view->setGeometry(QRect(10, 50, 84, 18));
    colorButton = new QPushButton(groupBox);
    colorButton->setObjectName(QString::fromUtf8("colorButton"));
    colorButton->setGeometry(QRect(10, 70, 111, 23));

    verticalLayout_2->addWidget(groupBox);

    groupBox_2 = new QGroupBox(widget);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy5.setHorizontalStretch(0);
    sizePolicy5.setVerticalStretch(5);
    sizePolicy5.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
    groupBox_2->setSizePolicy(sizePolicy5);
    gradientButton = new QRadioButton(groupBox_2);
    gradientButton->setObjectName(QString::fromUtf8("gradientButton"));
    gradientButton->setGeometry(QRect(10, 20, 84, 18));

    verticalLayout_2->addWidget(groupBox_2);

    verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_2->addItem(verticalSpacer_2);

    selectFileButton = new QPushButton(widget);
    selectFileButton->setObjectName(QString::fromUtf8("selectFileButton"));

    verticalLayout_2->addWidget(selectFileButton);


    horizontalLayout->addLayout(verticalLayout_2);


    verticalLayout_3->addLayout(horizontalLayout);

    splitter->addWidget(widget);
    tableView = new QTableView(splitter);
    tableView->setObjectName(QString::fromUtf8("tableView"));
    QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Minimum);
    sizePolicy6.setHorizontalStretch(0);
    sizePolicy6.setVerticalStretch(0);
    sizePolicy6.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
    tableView->setSizePolicy(sizePolicy6);
    splitter->addWidget(tableView);

    verticalLayout->addWidget(splitter);

    NanoAnalyzerClass->setCentralWidget(centralwidget);
    menubar = new QMenuBar(NanoAnalyzerClass);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 1298, 22));
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
    label_5->setText(QApplication::translate("NanoAnalyzerClass", "V(nm^2)", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("NanoAnalyzerClass", "-V(nm*2):", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("NanoAnalyzerClass", "dX(nm)(for .csv only):", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("NanoAnalyzerClass", "dY(nm):", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("NanoAnalyzerClass", "Step(for .csv only):", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("NanoAnalyzerClass", "View", 0, QApplication::UnicodeUTF8));
    points_view->setText(QApplication::translate("NanoAnalyzerClass", "points", 0, QApplication::UnicodeUTF8));
    lines_view->setText(QApplication::translate("NanoAnalyzerClass", "lines", 0, QApplication::UnicodeUTF8));
    shade_view->setText(QApplication::translate("NanoAnalyzerClass", "shade", 0, QApplication::UnicodeUTF8));
    colorButton->setText(QApplication::translate("NanoAnalyzerClass", "SetColor", 0, QApplication::UnicodeUTF8));
    groupBox_2->setTitle(QApplication::translate("NanoAnalyzerClass", "Gradient", 0, QApplication::UnicodeUTF8));
    gradientButton->setText(QApplication::translate("NanoAnalyzerClass", "gradient", 0, QApplication::UnicodeUTF8));
    selectFileButton->setText(QApplication::translate("NanoAnalyzerClass", "Select File", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(NanoAnalyzerClass);
    } // retranslateUi

};

namespace Ui {
    class NanoAnalyzerClass: public Ui_NanoAnalyzerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NANOANALYZER_H
