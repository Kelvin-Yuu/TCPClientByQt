#include "client.h"
#include "packet.h"

//ReadThread::ReadThread(QTcpSocket *socket)
//    : socket(socket)
//{

//}

//void ReadThread::run()
//{
//    QByteArray buffer;
//    while (true) {
//        if (socket->waitForReadyRead(-1)) {
//            buffer.append(socket->readAll());

//            while (buffer.size() >= 8) { // At least TL header
//                quint32 tag;
//                QByteArray data;
//                Packet::unpackData(buffer, tag, data);

//                quint32 totalLength = 8 + data.size();
//                if (buffer.size() >= totalLength) {
//                    buffer = buffer.mid(totalLength);

//                    emit dataReceived(tag, data);
//                } else {
//                    break; // Not enough data for complete message
//                }
//            }
//        }
//    }
//}

MyClient::MyClient(QString ip, quint16 port, QObject *parent)
    : QObject{parent}
     , ip(ip)
     , port(port)
{
    socket = new QTcpSocket(this);
    //readThread = new ReadThread(socket);

    //connect(readThread, &ReadThread::dataReceived, this, &MyClient::onDataReceived);
    connect(socket, &QTcpSocket::connected, this, &MyClient::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &MyClient::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &MyClient::onReadyRead);

    socket->connectToHost(ip,port);
}

void MyClient::sendData(quint32 tag, const QByteArray &data)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        QByteArray packet = Packet::packData(tag, data);

        socket->write(packet);
        socket->waitForBytesWritten(-1);
    }
}

void MyClient::onReadyRead()
{
    QByteArray buffer = socket->readAll();

    while (buffer.size() >= 8) { // At least TL header
        quint32 tag;
        QByteArray data;
        Packet::unpackData(buffer, tag, data);

        quint32 totalLength = 8 + data.size();
        if (buffer.size() >= totalLength) {
            buffer = buffer.mid(totalLength);

            emit sendMsgToMain(tag, data);
        } else {
            break; // Not enough data for complete message
        }
    }

}

//void MyClient::onDataReceived(quint32 tag, const QByteArray &data)
//{
//    emit sendMsgToMain(tag, data);
//}

void MyClient::onConnected()
{
    emit sendMsgToMain(1000, "Connected to server.");
}

void MyClient::onDisconnected()
{
    emit sendMsgToMain(1001, "Disconnected from server.");
}


