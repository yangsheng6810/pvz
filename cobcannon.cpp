#include <QDebug>
#include "cobcannon.h"
#define COB_RECHARGE_TIME 10

CobCannon::CobCannon(QObject *parent) :
    Plant("cobCannon")
{
    prepare = false;// for debug, should be false
    timer = new Timer(COB_RECHARGE_TIME);
    connect(timer,SIGNAL(timeout()),this,SLOT(recharge()));
    timer->start();
    // QTimer::singleShot(COB_RECHARGE_TIME*1000,this,SLOT(recharge()));
}

CobCannon::~CobCannon()
{
    timer->deleteLater();
}

QRectF CobCannon::boundingRect() const
{
    qreal adjust = 5;
    return QRectF(-18 - adjust, -22 - adjust,
                  200 + adjust, 140 + adjust);
}

QPainterPath CobCannon::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 200, 140);
    return path;
}

void CobCannon::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //painter->drawPixmap(0,0,QPixmap(":/images/"+plantName+".gif"));
    // painter->drawPixmap(0,0,movie->currentPixmap());
    painter->drawImage(xShift,yShift,movie->currentImage());
    painter->setBrush(QColor(127,0,0,127));
    if (prepare)
        painter->drawText(QPoint(0,0),"ready");
    else
        painter->drawText(QPoint(0,0),"charging");
    // painter->drawRect(0,0,90,100);
}

void CobCannon::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mousePressEvent(event);
    // qDebug()<<"come to CobCannon::mousePressEvent";
    if (!planted){
        event->ignore();
        return;
    }
    if (prepare){
        emit prepareToShoot(this);
        // qDebug()<<"having emit the signal";
        event->accept();
    }
    else
        event->ignore();
}

void CobCannon::shoot()
{
    // QTimer::singleShot(COB_RECHARGE_TIME,this,SLOT(recharge()));
    timer->start();
    prepare = false;
}

void CobCannon::recharge()
{
    prepare = true;
    timer->stop();
}

void CobCannon::pause()
{
    Plant::pause();
    timer->pause();
}

void CobCannon::restore()
{
    Plant::restore();
    timer->restore();
}
