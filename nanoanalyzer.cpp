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

	int i = 0;
	bool poins_started = false;
	while(!in.atEnd()) {
	    QString line = in.readLine();

	    if(poins_started){
			QStandardItem *firstRow = new QStandardItem(QString(line));
			model->setItem(i,0,firstRow);
			i++;
	    }

	    if(line.indexOf("Height(nm)") == 0){
	    	poins_started = true;
	    }
	}

	file.close();

	ui.tableView->setModel(model);
}
