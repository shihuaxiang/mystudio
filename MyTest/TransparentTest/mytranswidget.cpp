#include "mytranswidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>

QPixmap getFullScreenPixmap()
{
    QRect rect = QApplication::desktop()->geometry();
    QScreen *screen = QGuiApplication::primaryScreen();

    //QPixmap result = screen->grabWindow(QApplication::desktop()->winId(), rect.left(), rect.top(), rect.width(), rect.height());
    QPixmap result = screen->grabWindow(QApplication::desktop()->winId(), rect.left(), rect.top(), 500, 500);

    return result;
}

MyTransWidget::MyTransWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(500,500);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_DeleteOnClose);

    QLabel* label = new QLabel(this);
    label->setPixmap(getFullScreenPixmap());

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(label);
    this->setLayout(mainLayout);
}

MyTransWidget::~MyTransWidget()
{

}

void MyTransWidget::turnToSemiTrans()
{
    color = QColor(0, 0, 0, 150);
}

void MyTransWidget::turnToFullTrans()
{
     color = QColor(0, 0, 0, 0);
}

void MyTransWidget::paintEvent(QPaintEvent *event)
{
    QPixmap pixmap(this->size());
    pixmap.fill(color);

    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0, 0, pixmap);
    painter.end();
}
