#ifndef NANOANALYZER_H
#define NANOANALYZER_H

#include <QtGui/QMainWindow>
#include "ui_nanoanalyzer.h"

class NanoAnalyzer : public QMainWindow
{
    Q_OBJECT

public:
    NanoAnalyzer(QWidget *parent = 0);
    ~NanoAnalyzer();

private slots:
    void on_startButton_clicked();

private:
    Ui::NanoAnalyzerClass ui;
};

#endif // NANOANALYZER_H
