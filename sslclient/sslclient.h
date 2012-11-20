#ifndef SSLCLIENT_H
#define SSLCLIENT_H

#include <QObject>
#include <QSslSocket>

class SslClient : public QObject
{
    Q_OBJECT
public:
    explicit SslClient(QObject *parent = 0);

    void connectToHost(const QString& host, quint16 port);
signals:
    
public slots:
    void onConnected();
    void onEncrypted();
    void onReadyRead();
    void onDisConnected();
    void onError(QAbstractSocket::SocketError err);
    void onSslError(QList<QSslError>);
protected:
    QSslSocket *_socket;
};

#endif // SSLCLIENT_H
