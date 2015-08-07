#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebFrame>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initUrl(QString urlString);
    QWebFrame* getWebFrame();

private slots:
    void on_lineEdit_returnPressed();

    void on_actionCloudDisk_triggered();

    void on_actionPicturePpt_triggered();

    void on_actionPicturePptJs_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
