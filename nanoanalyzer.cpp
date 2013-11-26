#include "nanoanalyzer.h"
#include <QMouseEvent>
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qstandarditemmodel.h>
#include <qtextstream.h>
#include <QString>
#include <QtDebug>

NanoAnalyzer::NanoAnalyzer(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
	ui.dx->setValidator( new QDoubleValidator(-999.0, 999.0, 6, this) );
	ui.dy->setValidator( new QDoubleValidator(-999.0, 999.0, 6, this) );
	fileName = "";
}

NanoAnalyzer::~NanoAnalyzer()
{

}

void NanoAnalyzer::redraw()
{

	QStandardItemModel *model = new QStandardItemModel(200,3,this);
	model->setHorizontalHeaderItem(0, new QStandardItem(QString("x(nm)")));
	model->setHorizontalHeaderItem(1, new QStandardItem(QString("y(nm)")));
	model->setHorizontalHeaderItem(2, new QStandardItem(QString("z(nm)")));


	if(fileName != ""){

		QFile file(fileName);
		if(!file.open(QIODevice::ReadOnly)) {
			QMessageBox::information(0, "error", file.errorString());
		}

		QTextStream in(&file);

		QVector< QVector<float> > data_vector = QVector< QVector<float> >();

		bool poins_started = false;

		float max_x = 0;
		float min_x = 0;
		float max_y = 0;
		float min_y = 0;
		float max_z = 0;
		float min_z = 0;

		int rowPointsCount = 100;
		if(ui.rowPointsCount->value() > 0 ){
			rowPointsCount = ui.rowPointsCount->value();
		}

		float dx = 0.1;
		if(ui.dx->text() != "" ){
			dx = ui.dx->text().toFloat();
		}
		float dy = 0.1;
		if(ui.dy->text() != "" ){
			dy = ui.dy->text().toFloat();
		}
		float positive_v = 0;
		float negative_v = 0;
		int j = 0;

		while(!in.atEnd()) {
			if(poins_started){
				QVector<float> row;
				float positive_row_v = 0;
				float negative_row_v = 0;
				for(int i = 0; i < rowPointsCount; i++){
					if(in.atEnd()){
						row.push_back(0.0);
					}else{
						float point = in.readLine().toFloat();
						row.push_back(point);

						QStandardItem *z_cell = new QStandardItem(QString::number(point));
						model->setItem(((j*rowPointsCount) + i),2,z_cell);

						QStandardItem *y_cell = new QStandardItem(QString::number(j*dy));
						model->setItem(((j*rowPointsCount) + i),1,y_cell);

						QStandardItem *x_cell = new QStandardItem(QString::number(i*dx));
						model->setItem(((j*rowPointsCount) + i),0,x_cell);

						if(point > 0){
							positive_row_v += dx * point;
						}else{
							negative_row_v += dx * point;
						}

						float coord_x = dx * (i + 1);
						if( coord_x > max_x){
							max_x = coord_x;
						}
						if( coord_x < min_x){
							min_x = coord_x;
						}
						float coord_y = dy * (j + 1);
						if(coord_y > max_y){
							max_y = coord_y;
						}
						if(coord_y < min_y){
							min_y = coord_y;
						}
						if(point > max_z){
							max_z = point;
						}
						if(point < min_z){
							min_z = point;
						}

					}
				}
				j += 1;
				positive_v += positive_row_v * dy;
				negative_v += negative_row_v * dy;
				data_vector.push_back(row);
			}else{
				QString line = in.readLine();
				if(line.indexOf("Height(nm)") == 0){
					poins_started = true;
				}
			}

		}

		file.close();

	//	ui.tableView->setModel(model);
		ui.positive_v->setText(QString::number(positive_v));
		ui.negative_v->setText(QString::number(negative_v));
		QString drawtype = "lines";
		if(ui.points_view->isChecked()){
			drawtype = "points";
		}
		if(ui.lines_view->isChecked()){
			drawtype = "lines";
		}
		if(ui.shade_view->isChecked()){
			drawtype = "shade";
		}

//		QMessageBox::information(0, "max_x", QString::number(max_x));
//		QMessageBox::information(0, "max_y", QString::number(max_y));
//		QMessageBox::information(0, "max_z", QString::number(max_z));
//		QMessageBox::information(0, "min_x", QString::number(min_x));
//		QMessageBox::information(0, "min_y", QString::number(min_y));
//		QMessageBox::information(0, "min_z", QString::number(min_z));

		ui.modelView->setModelVector(data_vector, max_x, min_x, max_y, min_y, max_z, min_z, dx, dy, drawtype);

		ui.tableView->setModel(model);


	}
}

void NanoAnalyzer::on_selectFileButton_clicked(){
	fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));
	redraw();
}


void NanoAnalyzer::on_shade_view_clicked(){
	redraw();
}


void NanoAnalyzer::on_lines_view_clicked(){
	redraw();
}


void NanoAnalyzer::on_points_view_clicked(){
	redraw();
}

void NanoAnalyzer::on_rowPointsCount_valueChanged(int value){
	redraw();
}

void NanoAnalyzer::on_dy_textChanged(QString str){
	redraw();
}

void NanoAnalyzer::on_dx_textChanged(QString str){
	redraw();
}
