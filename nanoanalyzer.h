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
    void redraw();
    void on_selectFileButton_clicked();
    void on_shade_view_clicked();
    void on_lines_view_clicked();
    void on_points_view_clicked();
    void on_rowPointsCount_valueChanged(int value);
    void on_dy_textChanged(QString str);
    void on_dx_textChanged(QString str);
private:
    Ui::NanoAnalyzerClass ui;
	QString fileName;
};

#endif // NANOANALYZER_H
