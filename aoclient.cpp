#include "aoclient.h"

AOClient::AOClient(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &AOClient::readData);
    connect(socket, &QTcpSocket::connected, this, &AOClient::onConnect);
}

void AOClient::startConnection(QString ip, int port)
{
    disconnectFromHost();
    socket->connectToHost(ip, port);
}

void AOClient::disconnectFromHost()
{
    if (socket->state() != QAbstractSocket::UnconnectedState) {
        socket->abort();
    }
}

void AOClient::onConnect()
{

}

void AOClient::readData()
{
    QString socket_data = socket->readAll();
    QStringList all_packets = socket_data.split("%", QString::SplitBehavior(QString::SkipEmptyParts));
    for (QString packet_string : all_packets)
    {
        AOPacket packet(packet_string);
        qDebug() << "Received packet:" << packet.header << ":" << packet.contents;
        handlePacket(packet);
    }
}

void AOClient::handlePacket(AOPacket packet)
{
    if (packet.header == "decryptor") {
        // TODO: real hdid
        sendPacket("HI", {"abc123"});
    }
    else if (packet.header == "ID") {
        qDebug() << "Hello," << packet.contents[1];
    }
    else if (packet.header == "PN") {
        emit playerCount(packet.contents[0].toInt(), packet.contents[1].toInt());
    }
    else if (packet.header == "FL") {
        // TODO: handle fl
    }
    else {
        qDebug() << "UNIMPLEMENTED PACKET: " << packet.header;
    }
}

void AOClient::sendPacket(AOPacket packet)
{
    qDebug() << "Sent packet:" << packet.header << ":" << packet.contents;
    socket->write(packet.toUtf8());
    socket->flush();
}

void AOClient::sendPacket(QString header, QStringList contents)
{
    sendPacket(AOPacket(header, contents));
}

void AOClient::sendPacket(QString header)
{
    sendPacket(AOPacket(header, {}));
}

AOClient::~AOClient()
{
    socket->deleteLater();
}
