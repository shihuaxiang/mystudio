#ifndef GRAPHICSELLIPSEITEM_H
#define GRAPHICSELLIPSEITEM_H

#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <qmath.h>

class GraphicsEllipseItem : public QGraphicsEllipseItem
{
public:
    GraphicsEllipseItem();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    QPointF initialPos;
    qreal rotation;

};

#endif // GRAPHICSELLIPSEITEM_H
