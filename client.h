#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork>
#include <QThread>

//class ReadThread : public QThread
//{
//    Q_OBJECT
//public:
//    ReadThread(QTcpSocket *socket);

//protected:
//    void run() override;

//private:
//    QTcpSocket *socket;

//signals:
//    void dataReceived(quint32 tag, const QByteArray &data);

//};

class MyClient : public QObject
{
    Q_OBJECT
public:
    explicit MyClient(QString ip, quint16 port, QObject *parent = nullptr);

private:
    QTcpSocket *socket;
    //ReadThread *readThread;
    QString ip;
    quint16 port;

signals:
    void sendMsgToMain(quint32 tag, const QByteArray &data);

public slots:
    void sendData(quint32 tag, const QByteArray &data);

private slots:
   // void onDataReceived(quint32 tag, const QByteArray &data);
    void onConnected();
    void onDisconnected();
    void onReadyRead();
};

#endif // CLIENT_H
