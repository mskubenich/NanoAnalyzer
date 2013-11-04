#include "nanoanalyzer.h"
#include <QMouseEvent>
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qstandarditemmodel.h>
#include <qtextstream.h>


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
	while(!in.atEnd()) {
	    QString line = in.readLine();
//	    QStringList fields = line.split(",");
//	    model->appendRow(fields);

		QStandardItem *firstRow = new QStandardItem(QString(line));
		model->setItem(i,0,firstRow);
		i++;
	}

	file.close();

	ui.tableView->setModel(model);
}
