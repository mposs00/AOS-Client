#ifndef AOPACKET_H
#define AOPACKET_H

#include <QByteArray>
#include <QDebug>
#include <QString>
#include <QStringList>

class AOPacket {
  public:
    AOPacket(QString p_header, QStringList p_contents);
    AOPacket(QString packet);
    QString toString();
    QByteArray toUtf8();

    QString header;
    QStringList contents;
};


#endif // AOPACKET_H
