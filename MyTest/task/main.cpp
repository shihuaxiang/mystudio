#include "ProcessListWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ProcessListWidget w;
    w.show();

    return a.exec();
}
