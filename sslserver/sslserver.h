#ifndef SSLSERVER_H
#define SSLSERVER_H

#include <QTcpServer>
#include <QSslError>
#include <QTcpSocket>

class SSLServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit SSLServer(QObject *parent = 0);

    void start(quint16 port = 4433);
signals:
    
public slots:
    void onConnected();
    void onEncrypted();
    void onReadyRead();
    void onDisConnected();
    void onError(QAbstractSocket::SocketError err);
    void onSslError(QList<QSslError>);

    void onNewconnection();
protected:
    void incomingConnection(int socketDescriptor);

    QList<QTcpSocket*> _clients;
};

#endif // SSLSERVER_H
