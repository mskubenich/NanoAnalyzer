#include "nanoanalyzer.h"
#include <QMouseEvent>
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qstandarditemmodel.h>
#include <qtextstream.h>
#include <QString>
#include <QColorDialog>

NanoAnalyzer::NanoAnalyzer(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
	ui.dx->setValidator( new QDoubleValidator(-999.0, 999.0, 6, this) );
	ui.dy->setValidator( new QDoubleValidator(-999.0, 999.0, 6, this) );
}

NanoAnalyzer::~NanoAnalyzer()
{

}

void NanoAnalyzer::redraw()
{
	if(QString::compare(extension, "csv") == 0 || QString::compare(extension, "txt") == 0){
		draw_csv();
	}else if(QString::compare(extension, "dat") == 0){
		draw_dat();
	}
}

void NanoAnalyzer::on_selectFileButton_clicked(){
	QString theFileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));
	extension = theFileName.split(".").last().toLower();

	if(QString::compare(extension, "csv") == 0 || QString::compare(extension, "txt") == 0){
		read_csv(theFileName);
		draw_csv_table();
		redraw();
	}else if(QString::compare(extension, "dat") == 0){
		read_dat(theFileName);
		redraw();
	}
}
void NanoAnalyzer::on_colorButton_clicked(){
	ui.modelView->color = QColorDialog::getColor(ui.modelView->color, this);
	redraw();
}


void NanoAnalyzer::on_shade_view_clicked(){
	ui.modelView->drawtype = "shade";
	redraw();
}


void NanoAnalyzer::on_lines_view_clicked(){
	ui.modelView->drawtype = "lines";
	redraw();
}


void NanoAnalyzer::on_points_view_clicked(){
	ui.modelView->drawtype = "points";
	redraw();
}


void NanoAnalyzer::on_rowPointsCount_valueChanged(int value){
	redraw();
}

void NanoAnalyzer::on_dy_textChanged(QString str){
	redraw();
}

void NanoAnalyzer::on_slideSpinBox_valueChanged(double value){
	redraw();
}

void NanoAnalyzer::on_rows_count_valueChanged(int value){
	redraw();
}
void NanoAnalyzer::on_columns_count_valueChanged(int value){
	redraw();
}

void NanoAnalyzer::on_dx_textChanged(QString str){
	redraw();
}

void NanoAnalyzer::on_gradientCheckBox_clicked(bool value){
	if(ui.gradientCheckBox->isChecked()){
		ui.modelView->gradient = true;
	}else{
		ui.modelView->gradient = false;
	}
	redraw();
}

void NanoAnalyzer::on_draw_axes_checkbox_clicked(bool value){
	if(ui.draw_axes_checkbox->isChecked()){
		ui.modelView->draw_axes = true;
	}else{
		ui.modelView->draw_axes = false;
	}
	redraw();
}

void NanoAnalyzer::draw_csv(){
//	QStandardItemModel *model = new QStandardItemModel(200,3,this);
//	model->setHorizontalHeaderItem(0, new QStandardItem(QString("x(nm)")));
//	model->setHorizontalHeaderItem(1, new QStandardItem(QString("y(nm)")));
//	model->setHorizontalHeaderItem(2, new QStandardItem(QString("z(nm)")));
//
//	if(fileName != ""){
//
//		QFile file(fileName);
//		if(!file.open(QIODevice::ReadOnly)) {
//			QMessageBox::information(0, "error", file.errorString());
//		}
//
//		QTextStream in(&file);
//
//		QVector< QVector<float> > data_vector = QVector< QVector<float> >();
//
//		bool poins_started = false;
//
//		float max_x = 0;
//		float min_x = 0;
//		float max_y = 0;
//		float min_y = 0;
//		float max_z = 0;
//		float min_z = 0;
//
//		int rowPointsCount = 100;
//		if(ui.rowPointsCount->value() > 0 ){
//			rowPointsCount = ui.rowPointsCount->value();
//		}
//
//		float dx = 5.0;
//		if(ui.dx->text() != "" ){
//			dx = ui.dx->text().toFloat();
//		}else{
//		}
//		float dy = 5.0;
//		if(ui.dy->text() != "" ){
//			dy = ui.dy->text().toFloat();
//		}else{
//		}
//		float positive_v = 0;
//		float negative_v = 0;
//		int j = 0;
//
//		while(!in.atEnd()) {
//			if(poins_started){
//				QVector<float> row;
//				float positive_row_v = 0;
//				float negative_row_v = 0;
//				for(int i = 0; i < rowPointsCount; i++){
//					if(in.atEnd()){
//						row.push_back(0.0);
//					}else{
//						float point = in.readLine().toFloat() + (ui.slideSpinBox->value()*10);
//						row.push_back(point);
//
//						QStandardItem *z_cell = new QStandardItem(QString::number(point));
//						model->setItem(((j*rowPointsCount) + i),2,z_cell);
//
//						QStandardItem *y_cell = new QStandardItem(QString::number(j*dy));
//						model->setItem(((j*rowPointsCount) + i),1,y_cell);
//
//						QStandardItem *x_cell = new QStandardItem(QString::number(i*dx));
//						model->setItem(((j*rowPointsCount) + i),0,x_cell);
//
//						if(point > 0){
//							positive_row_v += dx * point;
//						}else{
//							negative_row_v += dx * point;
//						}
//
//						float coord_x = dx * (i + 1);
//						if( coord_x > max_x){
//							max_x = coord_x;
//						}
//						if( coord_x < min_x){
//							min_x = coord_x;
//						}
//						float coord_y = dy * (j + 1);
//						if(coord_y > max_y){
//							max_y = coord_y;
//						}
//						if(coord_y < min_y){
//							min_y = coord_y;
//						}
//						if(point > max_z){
//							max_z = point;
//						}
//						if(point < min_z){
//							min_z = point;
//						}
//
//					}
//				}
//				j += 1;
//				positive_v += positive_row_v * dy;
//				negative_v += negative_row_v * dy;
//				data_vector.push_back(row);
//			}else{
//				QString line = in.readLine();
//				if(line.indexOf("\"\\Samps") == 0 ){
//					int pointsCount = line.replace("\"\\Samps/line: ", "").replace("\"", "").toInt();
//					rowPointsCount = pointsCount;
//					ui.rowPointsCount->setValue(pointsCount);
//				}
//
//				if(line.indexOf("Height(nm)") == 0 || line.indexOf("Height_Sensor(nm)") == 0 ){
//					poins_started = true;
//				}
//			}
//
//		}
//
//		file.close();
//
//		ui.positive_v->setText(QString::number(positive_v));
//		ui.negative_v->setText(QString::number(negative_v));
//
//		int increment_x = data_vector[0].size()/ui.columns_count->value();
//		int increment_y = data_vector.size()/ui.rows_count->value();
//		if(increment_x < 1){
//			increment_x = 1;
//		}
//		if(increment_y < 1){
//			increment_y = 1;
//		}
//
//		QVector< QVector<float> > gl_data_vector = QVector< QVector<float> >();
//		for(int r = 0; r < data_vector.size(); r+=increment_y){
//			QVector<float> row;
//			for(int c = 0; c < data_vector[r].size(); c+=increment_x){
//				row.push_back(data_vector[r][c]);
//			}
//			gl_data_vector.push_back(row);
//		}
//
//		ui.modelView->setModelVector(gl_data_vector, max_x, min_x, max_y, min_y, max_z, min_z, dx*increment_x, dy*increment_y);
//
//		ui.tableView->setModel(model);
//	}
}


void NanoAnalyzer::draw_dat(){
//
//	QStandardItemModel *model = new QStandardItemModel(10,1,this);
//
//	if(fileName != ""){
//
//		QFile file(fileName);
//		if(!file.open(QIODevice::ReadOnly)) {
//			QMessageBox::information(0, "error", file.errorString());
//		}
//
//		QTextStream in(&file);
//
//		QVector< QVector<float> > data_vector = QVector< QVector<float> >();
//
//		float max = 0;
//		float maxy = 0;
//
//		int j = 0;
//		while(!in.atEnd()) {
//			if(in.atEnd()){
//
//			}else{
//				if(j == 0){
//					QString row = in.readLine();
//					QStringList columns = row.split(", ");
//					int c = 0;
//					while(c < columns.size()){
//						model->setHorizontalHeaderItem(c, new QStandardItem(QString(columns.at(c))));
//						data_vector.push_back(QVector<float>());
//						c++;
//					}
//				}else{
//					QString row = in.readLine();
//					QStringList columns = row.split(", ");
//					int c = 0;
//					while(c < columns.size()){
//						float float_value = QString(columns.at(c)).replace(",", ".").toFloat() - (ui.slideSpinBox->value()*10);
//						QStandardItem *cell = new QStandardItem(QString::number(float_value));
//						model->setItem(j - 1, c, cell);
//						data_vector[c].push_back(float_value);
//
//						if(c%2 == 0){
//							float value_mod = float_value;
//							if(value_mod < 0){
//								value_mod = value_mod * -1;
//							}
//							if(value_mod > max){
//								max = value_mod;
//							}
//						}else{
//							float value_mod = float_value;
//							if(value_mod < 0){
//								value_mod = value_mod * -1;
//							}
//							if(value_mod > maxy){
//								maxy = value_mod;
//							}
//						}
//
//						c++;
//					}
//				}
//			}
//			j += 1;
//		}
//
//		file.close();
//
//		ui.modelView->setDATModelVector(data_vector, max, maxy);
//
//		ui.tableView->setModel(model);
//
//
//	}
}


void NanoAnalyzer::read_csv(QString fileName){
	csv_data = QVector< float >();
	if(fileName != ""){

		QFile file(fileName);
		if(!file.open(QIODevice::ReadOnly)) {
			QMessageBox::information(0, "error", file.errorString());
		}

		QTextStream in(&file);

		QVector<float> data_vector = QVector<float>();

		bool poins_started = false;

		int rowPointsCount = 100;
		if(ui.rowPointsCount->value() > 0 ){
			rowPointsCount = ui.rowPointsCount->value();
		}

		float dx = 5.0;
		if(ui.dx->text() != "" ){
			dx = ui.dx->text().toFloat();
		}else{
		}
		float dy = 5.0;
		if(ui.dy->text() != "" ){
			dy = ui.dy->text().toFloat();
		}else{
		}

		int j = 0;

		while(!in.atEnd()) {
			if(poins_started){
				if(in.atEnd()){
					data_vector.push_back(0.0);
				}else{
					float point = in.readLine().toFloat();
					data_vector.push_back(point);
				}
				j += 1;
			}else{
				QString line = in.readLine();
				if(line.indexOf("\"\\Samps") == 0 ){
					int pointsCount = line.replace("\"\\Samps/line: ", "").replace("\"", "").toInt();
					rowPointsCount = pointsCount;
					ui.rowPointsCount->setValue(pointsCount);
				}

				if(line.indexOf("Height(nm)") == 0 || line.indexOf("Height_Sensor(nm)") == 0 ){
					poins_started = true;
				}
			}

		}

		file.close();
		csv_data = data_vector;
	}
}


void NanoAnalyzer::read_dat(QString filename){
//
//	if(fileName != ""){
//
//		QFile file(fileName);
//		if(!file.open(QIODevice::ReadOnly)) {
//			QMessageBox::information(0, "error", file.errorString());
//		}
//
//		QTextStream in(&file);
//
//		QVector< QVector<float> > data_vector = QVector< QVector<float> >();
//
//		float max = 0;
//		float maxy = 0;
//
//		int j = 0;
//		while(!in.atEnd()) {
//			if(in.atEnd()){
//
//			}else{
//				if(j == 0){
//					QString row = in.readLine();
//					QStringList columns = row.split(", ");
//					int c = 0;
//					while(c < columns.size()){
//						model->setHorizontalHeaderItem(c, new QStandardItem(QString(columns.at(c))));
//						data_vector.push_back(QVector<float>());
//						c++;
//					}
//				}else{
//					QString row = in.readLine();
//					QStringList columns = row.split(", ");
//					int c = 0;
//					while(c < columns.size()){
//						float float_value = QString(columns.at(c)).replace(",", ".").toFloat() - (ui.slideSpinBox->value()*10);
//						QStandardItem *cell = new QStandardItem(QString::number(float_value));
//						model->setItem(j - 1, c, cell);
//						data_vector[c].push_back(float_value);
//
//						if(c%2 == 0){
//							float value_mod = float_value;
//							if(value_mod < 0){
//								value_mod = value_mod * -1;
//							}
//							if(value_mod > max){
//								max = value_mod;
//							}
//						}else{
//							float value_mod = float_value;
//							if(value_mod < 0){
//								value_mod = value_mod * -1;
//							}
//							if(value_mod > maxy){
//								maxy = value_mod;
//							}
//						}
//
//						c++;
//					}
//				}
//			}
//			j += 1;
//		}
//
//		file.close();
//
//		ui.modelView->setDATModelVector(data_vector, max, maxy);
//
//		ui.tableView->setModel(model);
//
//
//	}
}


void NanoAnalyzer::draw_csv_table(){
	QStandardItemModel *model = new QStandardItemModel(200,3,this);
	model->setHorizontalHeaderItem(0, new QStandardItem(QString("x(nm)")));
	model->setHorizontalHeaderItem(1, new QStandardItem(QString("y(nm)")));
	model->setHorizontalHeaderItem(2, new QStandardItem(QString("z(nm)")));

	int rowPointsCount = 100;
	if(ui.rowPointsCount->value() > 0 ){
		rowPointsCount = ui.rowPointsCount->value();
	}

	float dx = 5.0;
	if(ui.dx->text() != "" ){
		dx = ui.dx->text().toFloat();
	}else{
	}
	float dy = 5.0;
	if(ui.dy->text() != "" ){
		dy = ui.dy->text().toFloat();
	}else{
	}
	float positive_v = 0;
	float negative_v = 0;

	int i = 0;
	float x_value = 0;
	float y_value = -5;
	while( i < csv_data.size()){
		float point = csv_data[i] + (ui.slideSpinBox->value()*10);
		QStandardItem *z_cell = new QStandardItem(QString::number(point));
		model->setItem(i,2,z_cell);

		if(i%rowPointsCount == 0){
			x_value = 0;
			y_value += dy;
		}

		QStandardItem *x_cell = new QStandardItem(QString::number(x_value));
		model->setItem(i,0,x_cell);

		QStandardItem *y_cell = new QStandardItem(QString::number(y_value));
		model->setItem(i,1,y_cell);

		x_value += dx;

		i++;
	}

//	int j = 0;
//	while(j < csv_data.size()){
//
//		float positive_row_v = 0;
//		float negative_row_v = 0;
//
//		for(int i = 0; i < rowPointsCount; i++){
//			if(j < csv_data.size()){
//
//
//				if(point > 0){
//					positive_row_v += dx * point;
//				}else{
//					negative_row_v += dx * point;
//				}
//				j++;
//			}
//		}
//		positive_v += positive_row_v * dy;
//		negative_v += negative_row_v * dy;
//	}
//

	ui.positive_v->setText(QString::number(positive_v));
	ui.negative_v->setText(QString::number(negative_v));

	ui.tableView->setModel(model);
}


void NanoAnalyzer::draw_dat_table(){
//
//	QStandardItemModel *model = new QStandardItemModel(10,1,this);
//
//	if(fileName != ""){
//
//		QFile file(fileName);
//		if(!file.open(QIODevice::ReadOnly)) {
//			QMessageBox::information(0, "error", file.errorString());
//		}
//
//		QTextStream in(&file);
//
//		QVector< QVector<float> > data_vector = QVector< QVector<float> >();
//
//		float max = 0;
//		float maxy = 0;
//
//		int j = 0;
//		while(!in.atEnd()) {
//			if(in.atEnd()){
//
//			}else{
//				if(j == 0){
//					QString row = in.readLine();
//					QStringList columns = row.split(", ");
//					int c = 0;
//					while(c < columns.size()){
//						model->setHorizontalHeaderItem(c, new QStandardItem(QString(columns.at(c))));
//						data_vector.push_back(QVector<float>());
//						c++;
//					}
//				}else{
//					QString row = in.readLine();
//					QStringList columns = row.split(", ");
//					int c = 0;
//					while(c < columns.size()){
//						float float_value = QString(columns.at(c)).replace(",", ".").toFloat() - (ui.slideSpinBox->value()*10);
//						QStandardItem *cell = new QStandardItem(QString::number(float_value));
//						model->setItem(j - 1, c, cell);
//						data_vector[c].push_back(float_value);
//
//						if(c%2 == 0){
//							float value_mod = float_value;
//							if(value_mod < 0){
//								value_mod = value_mod * -1;
//							}
//							if(value_mod > max){
//								max = value_mod;
//							}
//						}else{
//							float value_mod = float_value;
//							if(value_mod < 0){
//								value_mod = value_mod * -1;
//							}
//							if(value_mod > maxy){
//								maxy = value_mod;
//							}
//						}
//
//						c++;
//					}
//				}
//			}
//			j += 1;
//		}
//
//		file.close();
//
//		ui.modelView->setDATModelVector(data_vector, max, maxy);
//
//		ui.tableView->setModel(model);
//
//
//	}
}
