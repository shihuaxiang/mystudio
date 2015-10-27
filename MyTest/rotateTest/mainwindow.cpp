#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    QRect rectangle[3] = { QRect(-40, -30, 80, 60), QRect(10, 20, 80, 60), QRect(50, 80, 80, 60) };
    QColor color[3] = { Qt::red, Qt::yellow, Qt::blue};

    GraphicsEllipseItem *item;
    for (int i = 0; i < 3; i++)
    {
        item = new GraphicsEllipseItem();
        item->setBrush(QBrush(color[i]));
        item->setRect(rectangle[i]);
        scene->addItem(item);

        items[i] = item;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
