#include "nanoanalyzer.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NanoAnalyzer w;
    w.show();
    return a.exec();
}
