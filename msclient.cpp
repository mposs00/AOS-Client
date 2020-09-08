#include "msclient.h"

MSClient::MSClient(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::connected, this, &MSClient::msConnected);
    connect(socket, &QTcpSocket::readyRead, this, &MSClient::readSocket);
}

void MSClient::msConnect()
{
    // TODO: configurable
    socket->connectToHost("master.aceattorneyonline.com", 27016);
    loadServerList();
}

void MSClient::loadServerList()
{
    socket->write(AOPacket("ALL", {}).toUtf8());
    socket->flush();
}

void MSClient::readSocket()
{
    QString ms_data = socket->readAll();

    if (!ms_data.endsWith("%")) {
        partial_data += ms_data;
        is_partial = true;
        return;
    }

    if (is_partial) {
        is_partial = false;
        ms_data = partial_data + ms_data;
        partial_data = "";
    }

    QStringList all_packets = ms_data.split("%", QString::SplitBehavior(QString::SkipEmptyParts));
    for (QString packet : all_packets) {
        AOPacket ms_packet(packet);
        if (ms_packet.header == "ALL") {
            emit msUpdated();
            for (QString server : ms_packet.contents) {
                emit serverData(server);
            }
        }
    }
}

void MSClient::msConnected()
{
    qDebug() << "Connected to master server";
}

void MSClient::msDisconnected()
{

}

MSClient::~MSClient()
{
    socket->deleteLater();
}
