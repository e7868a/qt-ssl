#include "sslserver.h"
#include <QSslSocket>
#include <QSslCipher>
#include <QSslKey>
#include <QDebug>

SSLServer::SSLServer(QObject *parent) :
    QTcpServer(parent)
{
    connect(this, SIGNAL(newConnection()), SLOT(onNewconnection()));
}

void
SSLServer::incomingConnection(int socketDescriptor)
{
    QSslSocket *socket = new QSslSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
    this->addPendingConnection(socket);
}

void
SSLServer::onConnected()
{
    qDebug() << "connected";
}

void
SSLServer::onEncrypted()
{
    qDebug() << "encrypted";
}

void
SSLServer::onReadyRead()
{
    qDebug() << "readyread";

    QSslSocket *sck = (QSslSocket*)sender();
    QByteArray ar = sck->readAll();
    QString str = QString::fromUtf8(ar.constData());
    qDebug() << str;

    // echo back
    sck->write(ar);
}

void
SSLServer::onDisConnected()
{
    qDebug() << "disconnected";
    _clients.removeOne((QTcpSocket*)sender());
    qDebug() << "client count: " << _clients.count();
}

void
SSLServer::onError(QAbstractSocket::SocketError err)
{
    qDebug() << "error: " << err << ((QSslSocket*)sender())->errorString();
}

void
SSLServer::onSslError(QList<QSslError> errs)
{
    Q_FOREACH(const QSslError& err, errs) {
        qDebug() << "SslError: " << err;
    }
}

void
SSLServer::start(quint16 port)
{
    if (!this->listen(QHostAddress::Any, port)) {
        qDebug() << "listen failed: " << this->errorString();
    }
}

void
SSLServer::onNewconnection()
{
    QTcpSocket *sck = this->nextPendingConnection();
    if (!sck) return;

    qDebug() << "newconnection: " << sck;
    QSslSocket *socket = qobject_cast<QSslSocket*>(sck);

    connect(socket, SIGNAL(connected()), SLOT(onConnected()));
    connect(socket, SIGNAL(encrypted()), SLOT(onEncrypted()));
    connect(socket, SIGNAL(readyRead()), SLOT(onReadyRead()));
    connect(socket, SIGNAL(disconnected()), SLOT(onDisConnected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(onError(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(sslErrors(QList<QSslError>)), SLOT(onSslError(QList<QSslError>)));

    socket->setLocalCertificate("server.crt");
    socket->setPrivateKey("server.pem");
    Q_ASSERT(!socket->localCertificate().isNull());
    Q_ASSERT(!socket->privateKey().isNull());

    socket->setProtocol(QSsl::TlsV1SslV3);

    socket->startServerEncryption();

    _clients << sck;
}
