#include "nanoanalyzer.h"
#include <QMouseEvent>
#include <qmessagebox.h>
#include <qfiledialog.h>

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
	QMessageBox::information(this, "Hello World!", fileName);
}
