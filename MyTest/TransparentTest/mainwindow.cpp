#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytranswidget.h"
#include <QDebug>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    transWidget = new MyTransWidget();
    transWidget->hide();
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;  
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    qDebug() << "Timer ID:" << event->timerId();

    QApplication::alert(this,1000);
}

void MainWindow::on_pushButton_clicked()
{
    //semi trans
    transWidget->turnToSemiTrans();
    transWidget->repaint();
    transWidget->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    //full trans
    transWidget->turnToFullTrans();
    transWidget->repaint();
    transWidget->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    transWidget->close();
}

void MainWindow::on_pushButton_4_clicked()
{
    startTimer(20000);
    this->showMinimized();
}
