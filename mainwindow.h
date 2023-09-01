#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_cntButton_clicked();
    void receive_tcp_msg(quint32 tag, const QByteArray &data);


private:
    Ui::MainWindow *ui;
    MyClient *client;
    QString ip;
    quint16 port;
};
#endif // MAINWINDOW_H
