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
	model->setHorizontalHeaderItem(0, new QStandardItem(QString("x")));
	model->setHorizontalHeaderItem(1, new QStandardItem(QString("y")));
	model->setHorizontalHeaderItem(2, new QStandardItem(QString("z")));

	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly)) {
	    QMessageBox::information(0, "error", file.errorString());
	}

	QTextStream in(&file);

	QVector<float> data_vector;
	int i = 0;
	float current_x = 0;
	float current_y = 0;
	bool poins_started = false;
	while(!in.atEnd()) {
	    QString line = in.readLine();

	    if(poins_started){
	    	data_vector.push_back(line.toFloat());

			QStandardItem *z_cell = new QStandardItem(QString::number(line.toFloat()));
			model->setItem(i,2,z_cell);

			current_x = current_x + 0.1e+002;
			QStandardItem *x_cell = new QStandardItem(QString::number(current_x));
			model->setItem(i,0,x_cell);

		    if(i%100 == 0){
		    	current_x = 0;
		    	current_y = current_y + 0.1e+002;
		    }

			QStandardItem *y_cell = new QStandardItem(QString::number(current_y));
			model->setItem(i,1,y_cell);

			i++;
	    }

	    if(line.indexOf("Height(nm)") == 0){
	    	poins_started = true;
	    }
	}

	file.close();

	ui.tableView->setModel(model);
	ui.modelView->setModelVector(&data_vector);
}
