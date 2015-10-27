#ifndef KEYPRESSEATER_H
#define KEYPRESSEATER_H

#include <QObject>
#include <QEvent>

class KeyPressEater : public QObject
{
    Q_OBJECT
public:
    explicit KeyPressEater(QObject *parent = 0);
    ~KeyPressEater();

signals:

public slots:

protected:
    bool eventFilter(QObject *obj, QEvent *event);

};

#endif // KEYPRESSEATER_H
