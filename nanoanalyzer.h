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
    void draw_csv();
    void draw_dat();

    void draw_csv_table();
    void draw_dat_table();

    void read_csv(QString filename);
    void read_dat(QString filename);

    void on_selectFileButton_clicked();
    void on_colorButton_clicked();
    void on_shade_view_clicked();
    void on_lines_view_clicked();
    void on_points_view_clicked();
    void on_rowPointsCount_valueChanged(int value);
    void on_slideSpinBox_valueChanged(double value);
    void on_dy_textChanged(QString str);
    void on_dx_textChanged(QString str);
    void on_gradientCheckBox_clicked(bool value);
    void on_draw_axes_checkbox_clicked(bool value);
    void on_rows_count_valueChanged(int value);
    void on_columns_count_valueChanged(int value);
private:
    Ui::NanoAnalyzerClass ui;
    QString extension;

    QVector< float > csv_data;
};

#endif // NANOANALYZER_H
