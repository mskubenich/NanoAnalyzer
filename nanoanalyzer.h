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
    void on_drawButton_clicked();
    void on_selectFileButton_clicked();

private:
    Ui::NanoAnalyzerClass ui;
	QString fileName;
};

#endif // NANOANALYZER_H
