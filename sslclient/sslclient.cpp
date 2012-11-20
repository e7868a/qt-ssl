#include "sslclient.h"
#include <QDebug>
#include <QCoreApplication>

SslClient::SslClient(QObject *parent) :
    QObject(parent)
{
    _socket = new QSslSocket(this);

    connect(_socket, SIGNAL(connected()), SLOT(onConnected()));
    connect(_socket, SIGNAL(encrypted()), SLOT(onEncrypted()));
    connect(_socket, SIGNAL(readyRead()), SLOT(onReadyRead()));
    connect(_socket, SIGNAL(disconnected()), SLOT(onDisConnected()));
    connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(onError(QAbstractSocket::SocketError)));
    connect(_socket, SIGNAL(sslErrors(QList<QSslError>)), SLOT(onSslError(QList<QSslError>)));
}

void
SslClient::onConnected()
{
    qDebug() << "connected";
}

void
SslClient::onEncrypted()
{
    qDebug() << "encrypted";
    _socket->write(QString("GET /\r\n\r\n").toUtf8());
}

void
SslClient::onReadyRead()
{
    qDebug() << "readyread";
    QString ret = QString::fromUtf8(_socket->readAll().constData());
    qDebug() << ret;
}

void
SslClient::onDisConnected()
{
    qDebug() << "disconnected";
    QCoreApplication::exit();
}

void
SslClient::onError(QAbstractSocket::SocketError err)
{
    qDebug() << "error: " << err;
}

void
SslClient::connectToHost(const QString &host, quint16 port)
{
    qDebug() << "connecting";
    _socket->connectToHostEncrypted(host, port);
}

void
SslClient::onSslError(QList<QSslError> errs)
{
    _socket->ignoreSslErrors();

    Q_FOREACH(const QSslError& err, errs) {
        qDebug() << "SslError: " << err;
    }
}
