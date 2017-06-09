#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QTimer>
#include <cstring>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    //tcpConnect();
    time=new QTimer(this);

    connect(ui->connect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpConnect()));
    connect(ui->disconnect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpDisconnect()));
    connect(ui->pushButtonstart,
            SIGNAL(clicked(bool)),
            this,
            SLOT(on_start_clicked()));
    connect(ui->pushButtonstop,
            SIGNAL(clicked(bool)),
            this,
            SLOT(on_stop_clicked()));
    connect(time,
            SIGNAL(timeout()),
            this,
            SLOT(putdata()));

}

void MainWindow::tcpConnect(){

    socket->connectToHost( ui->lineEdit->text(),1234);
    if(socket->waitForConnected(3000)){
       ui->textout->append("Connected \n");
    }
    else{
        ui->textout->append("Disconnected\n");
        qDebug() << "Disconnected";
    }
}

void MainWindow::putData()
{
    QDateTime datetime;
    QString str;
    int min,max;
    min=ui->horizontalSliderMIN->value();
    max=ui->horizontalSliderMAX->value();
    if(socket->state()== QAbstractSocket::ConnectedState){
        datetime = QDateTime::currentDateTime();
        str = "set "+
                datetime.toString(Qt::ISODate)+
                " "+
                QString::number(min+qrand()%(max-min))+"/r/n";

        ui->textout->append(str);
        qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
        if(socket->waitForBytesWritten(3000)){
            qDebug() << "wrote";
        }
    }
    else {
        qDebug()<<"conexão perdida \n";
    }
}

void MainWindow::timerEvent(QTimerEvent *e)
{

    putData();


}


MainWindow::~MainWindow()
{
    delete socket;
    delete ui;
}

void MainWindow::tcpDisconnect()
{
    killTimer(id);
    //time->stop();
    socket->disconnectFromHost();
    qDebug()<<"Disconnected";
}

void MainWindow::on_start_clicked()
{
    id=startTimer(ui->horizontalSliderTIME->value()*1000);
    //time->start(ui->horizontalSliderTIME->value()*1000);
}

void MainWindow::on_stop_clicked()
{

    killTimer(id);
    //time->stop();
}
