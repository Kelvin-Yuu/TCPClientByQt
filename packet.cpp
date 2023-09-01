#include "packet.h"

QByteArray Packet::packData(quint32 tag, const QByteArray &data)
{
    QByteArray packet;

    packet.append(static_cast<char>(tag & 0xFF));
    packet.append(static_cast<char>((tag >> 8) & 0xFF));
    packet.append(static_cast<char>((tag >> 16) & 0xFF));
    packet.append(static_cast<char>((tag >> 24) & 0xFF));

    quint32 length = static_cast<quint32>(data.size());
    packet.append(static_cast<char>(length & 0xFF));
    packet.append(static_cast<char>((length >> 8) & 0xFF));
    packet.append(static_cast<char>((length >> 16) & 0xFF));
    packet.append(static_cast<char>((length >> 24) & 0xFF));

    packet.append(data);

    return packet;
}


void Packet::unpackData(const QByteArray &buffer, quint32 &tag, QByteArray &data)
{
    tag = static_cast<quint32>(
        (buffer[3] << 24) |
        (buffer[2] << 16) |
        (buffer[1] << 8) |
        buffer[0]
        );

    quint32 length = static_cast<quint32>(
        (buffer[7] << 24) |
        (buffer[6] << 16) |
        (buffer[5] << 8) |
        buffer[4]
        );

    data = buffer.mid(8, length);

}
