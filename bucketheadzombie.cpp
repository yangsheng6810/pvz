#include "bucketheadzombie.h"

BucketheadZombie::BucketheadZombie(Field* ff,QObject *parent) :
    Zombie(ff, "bucketheadZombie", parent)
{
    healthPoint = 30;
    xShift = 0;
    yShift = -40;
}

QRectF BucketheadZombie::boundingRect() const
{
    qreal adjust = 5;
    return QRectF( xShift- adjust, yShift - adjust,
                  100 + adjust, 170 + adjust);
}

QPainterPath BucketheadZombie::shape() const
{
    QPainterPath path;
    qreal adjust = -5;
    path.addRect(xShift - adjust, yShift - adjust, 100 + adjust, 170 + adjust);
    return path;
}
