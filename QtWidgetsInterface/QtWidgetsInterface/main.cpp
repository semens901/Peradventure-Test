#include "QtInterface.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtInterface w;
    w.show();
    return a.exec();
}
