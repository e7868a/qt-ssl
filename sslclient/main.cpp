#include <QCoreApplication>
#include "sslclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SslClient *client = new SslClient();
    client->connectToHost("127.0.0.1", 4433);
    
    return a.exec();
}
