#include "graphicsellipseitem.h"


GraphicsEllipseItem::GraphicsEllipseItem()
{
    rotation = 0;
    setFlags(flags() | QGraphicsItem::ItemIsSelectable);
}

void GraphicsEllipseItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    initialPos = mapToScene(event->pos());
    QGraphicsItem::mousePressEvent(event);
}

void GraphicsEllipseItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = mapToScene(event->pos());

    if (pos.y() > initialPos.y()) {
        ++rotation;
    } else {
        --rotation;
    }

#if 0
    QTransform xform;
    xform.rotate(rotation);
    //xform.scale(qPow(1.2,scaleValue.x()),qPow(1.2,scaleValue.y()));
    setTransform(xform);
#else
    setRotation(rotation);
#endif
    initialPos = pos;
}
