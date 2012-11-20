#include <QCoreApplication>
#include "sslserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SSLServer *server = new SSLServer();
    server->start();

    return a.exec();
}
