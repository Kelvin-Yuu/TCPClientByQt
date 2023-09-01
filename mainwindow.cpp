#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = nullptr;
}

MainWindow::~MainWindow()
{
    if (client != nullptr) {
        delete client;
        client = nullptr;
    }
    delete ui;
}


void MainWindow::on_cntButton_clicked()
{
    ip = ui->ipEdit->toPlainText();
    port = ui->portEdit->toPlainText().toUShort();
    ui->outputEdit->appendPlainText("正在与IP:" + ip + ":" + QString::number(port) + "建立TCP连接");
    client = new MyClient(ip, port);

    connect(client, &MyClient::sendMsgToMain, this, &MainWindow::receive_tcp_msg);


}

void MainWindow::receive_tcp_msg(quint32 tag, const QByteArray &data)
{
    if (1000 == tag) {
        ui->outputEdit->appendPlainText("成功与IP:" + ip + ":" + QString::number(port) + "建立TCP连接");
        client->sendData(1, "Hello Server!");
    } else if (1001 == tag) {
        ui->outputEdit->appendPlainText("成功与IP:" + ip + ":" + QString::number(port) + "断开TCP连接");
    } else {
        ui->outputEdit->appendPlainText("收到来着Server的消息: [tag]:" + QString::number(tag) + " [data]:" + data);
    }

}




