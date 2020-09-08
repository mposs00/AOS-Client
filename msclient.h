#ifndef MSCLIENT_H
#define MSCLIENT_H

#include "aopacket.h"

#include <QObject>
#include <QString>
#include <QTcpSocket>

class MSClient : public QObject
{
    Q_OBJECT
public:
    explicit MSClient(QObject *parent = nullptr);

public slots:
    void msConnect();
    void loadServerList();

private slots:
    void readSocket();
    void msConnected();
    void msDisconnected();

signals:
    void serverData(QString server);
    void msUpdated();

private:
    QTcpSocket* socket = nullptr;
    QString partial_data = "";
    bool is_partial = false;
};

#endif // MSCLIENT_H
