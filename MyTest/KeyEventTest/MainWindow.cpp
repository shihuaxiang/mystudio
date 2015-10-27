#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "KeyPressEater.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    KeyPressEater *keyPressEater = new KeyPressEater(this);
    ui->textEdit->installEventFilter(keyPressEater);
    ui->webView->installEventFilter(keyPressEater);
}

MainWindow::~MainWindow()
{
    delete ui;
}
