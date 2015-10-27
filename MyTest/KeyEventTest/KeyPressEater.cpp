#include <QKeyEvent>
#include "KeyPressEater.h"

KeyPressEater::KeyPressEater(QObject *parent) : QObject(parent)
{

}

KeyPressEater::~KeyPressEater()
{

}

bool KeyPressEater::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        qDebug("Ate key press %d", keyEvent->key());

        if(keyEvent->key() == Qt::Key_PageUp ||
                keyEvent->key() == Qt::Key_PageDown ||
                keyEvent->key() == Qt::Key_Up ||
                keyEvent->key() == Qt::Key_Down)
        {
            return true;
        }
    }

    // standard event processing
    return QObject::eventFilter(obj, event);
}
