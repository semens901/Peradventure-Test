#include <QtCore/QCoreApplication>
#include "ServerNetwork.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ServerNetwork server;
    return a.exec();
}
