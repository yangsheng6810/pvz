#include "coneheadzombie.h"

ConeheadZombie::ConeheadZombie(Field* ff, QObject *parent) :
    Zombie(ff, "coneheadZombie" ,parent)
{
    healthPoint = 20;
    xShift = 0;
    yShift = -30;
}

QRectF ConeheadZombie::boundingRect() const
{
    qreal adjust = 5;
    return QRectF( xShift - adjust, yShift - adjust,
                  90 + adjust, 170 + adjust);
}

QPainterPath ConeheadZombie::shape() const
{
    QPainterPath path;
    qreal adjust = -5;
    path.addRect(xShift - adjust, yShift - adjust, 90 + adjust, 170 + adjust);
    return path;
}
