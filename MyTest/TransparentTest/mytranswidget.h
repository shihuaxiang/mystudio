#ifndef MYTRANSWIDGET_H
#define MYTRANSWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class MyTransWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyTransWidget(QWidget *parent = 0);
    ~MyTransWidget();
    void turnToSemiTrans();
    void turnToFullTrans();

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);

private:
    QColor color;

};

#endif // MYTRANSWIDGET_H
