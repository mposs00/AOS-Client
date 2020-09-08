#ifndef AOCLIENT_H
#define AOCLIENT_H

#include <aopacket.h>

#include <QDebug>
#include <QObject>
#include <QStringList>
#include <QTcpSocket>

class AOClient : public QObject
{
    Q_OBJECT
public:
    explicit AOClient(QObject *parent = nullptr);
    ~AOClient();

    void startConnection(QString ip, int port);
    void disconnectFromHost();

public slots:

private slots:
    void readData();
    void onConnect();

signals:
    void playerCount(int current, int max);

private:
    void handlePacket(AOPacket packet);
    void sendPacket(AOPacket packet);
    void sendPacket(QString header, QStringList contents);
    void sendPacket(QString header);

    QTcpSocket* socket;
};

#endif // AOCLIENT_H
