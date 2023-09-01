#ifndef PACKET_H
#define PACKET_H

#include <QObject>

class Packet {
public:
    static QByteArray packData(quint32 tag, const QByteArray &data);

    static void unpackData(const QByteArray &buffer, quint32 &tag, QByteArray &data);
};
#endif // PACKET_H
