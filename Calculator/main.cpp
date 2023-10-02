#include "calculator.h"

#include <QApplication>
#include <qfile.h>
#include <qtextstream.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;
    w.show();

    return a.exec();
}

