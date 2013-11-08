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
	ui.rowPointsCount->setValidator( new QIntValidator(0, 100, this) );
	ui.dx->setValidator( new QDoubleValidator(-999.0, 999.0, 6, this) );
	ui.dy->setValidator( new QDoubleValidator(-999.0, 999.0, 6, this) );
}

NanoAnalyzer::~NanoAnalyzer()
{

}

void NanoAnalyzer::on_startButton_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
	                                                 "",
	                                                 tr("Files (*.*)"));

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

		float max_z = 0;
		float min_z = 0;

		int rowPointsCount = 100;
		if(ui.rowPointsCount->text() != "" ){
			rowPointsCount = ui.rowPointsCount->text().toInt();
		}

		float dx = 0.1;
		if(ui.dx->text() != "" ){
			dx = ui.dx->text().toFloat();
		}
		float dy = 0.1;
		if(ui.dy->text() != "" ){
			dy = ui.dy->text().toFloat();
		}
		float v = 0;
		int j = 0;

		while(!in.atEnd()) {
			if(poins_started){
				QVector<float> row;
				float row_v = 0;
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

						row_v += dx * point;

						if(point > max_z){
							max_z = point;
						}
						if(point < min_z){
							min_z = point;
						}

					}
				}
				j += 1;
				v += row_v * dy;
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
		ui.v->setText(QString::number(v));
		ui.modelView->setModelVector(data_vector, max_z, min_z);

		ui.tableView->setModel(model);
	}
}
