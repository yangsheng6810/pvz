#include "target.h"

Target::Target(QObject *parent)
{
}

int Target::type() const
{
    return Type;
}

QRectF Target::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(0  - adjust, 0  - adjust,
                  80 + adjust, 80 + adjust);
}

QPainterPath Target::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 70, 70);
    return path;
}

void Target::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0,0,QPixmap(":/images/target.png"));
}
