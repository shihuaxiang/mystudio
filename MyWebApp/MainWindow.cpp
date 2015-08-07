#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->webView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    initUrl("https://pan.baidu.com/");
    //initUrl("http://v.youku.com/v_playlist/f16675792o1p1.html");
    //initUrl("http://v.qq.com/cover/y/y3087mc8t3p13fj.html?vid=b0017rtmlwa");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUrl(QString urlString)
{
    ui->lineEdit->setText(urlString);
    ui->webView->setUrl(QUrl(urlString));
}

QWebFrame* MainWindow::getWebFrame()
{
    return ui->webView->page()->mainFrame();
}

void MainWindow::on_lineEdit_returnPressed()
{
    ui->webView->setUrl(QUrl(ui->lineEdit->text()));
}

void MainWindow::on_actionCloudDisk_triggered()
{
    //initUrl("http://www.eeoa.test/cloud/index.php?userid=1000150&folder_id=200&pc=3");
    initUrl("http://www.eeoa.test/cloud/index.php?userid=1000150&folder_id=200&pc=0");
}

void MainWindow::on_actionPicturePpt_triggered()
{
    initUrl("http://www.eeoa.test/cloud/pptshow.html");
}

void MainWindow::on_actionPicturePptJs_triggered()
{
    QString js = QString("loadPPTFile('230-1000150',0)");
    getWebFrame()->evaluateJavaScript(js);
}
