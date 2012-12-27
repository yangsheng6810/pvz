#include "sun.h"
#include <QDebug>

Sun::Sun(int sun,QObject *parent) :
    sunLight(sun)
{
    // qDebug()<<"come to Sun::Sun";
}

QRectF Sun::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(0  - adjust, 0  - adjust,
                  40 + adjust, 40 + adjust);
}

QPainterPath Sun::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 40, 40);
    return path;
}

void Sun::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0,0,QPixmap(":/images/sun.png"));
}

void Sun::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    // qDebug()<<"visit Sun::mousePressEvent";
    emit emitSun(sunLight);
    emit destroyMe(this);
    // deleteLater();
}
