#include "cob.h"
#include "Constants.h"
#include <QTimer>
#include <QDebug>
#define COB_FLY_TIME 3

Cob::Cob(QPoint &p):
target(p)
{
    setZValue(20);
    transform.rotate(180);
    up = true;
    // QTimer::singleShot(COB_FLY_TIME*1000,this,SLOT(reverse()));
    timer = new Timer(COB_FLY_TIME);
    timer->setSingleShot();
    connect(timer,SIGNAL(timeout()),this,SLOT(reverse()));
    timer->start();
    // qDebug()<<"Cob at location "<<(long)this;
}

Cob::~Cob()
{
    timer->deleteLater();
}

int Cob::type() const
{
    return Type;
}

QRectF Cob::boundingRect() const
{
    qreal adjust = 5;
    return QRectF(0 - adjust, 0 - adjust,
                  100 + adjust, 180 + adjust);
}

QPainterPath Cob::shape() const
{
    QPainterPath path;
    path.addRect(0,0,78,162);
    return path;
}

void Cob::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (up)
        painter->drawPixmap(0,0,QPixmap(":/images/cob.png"));
    else
        painter->drawPixmap(0,0,QPixmap(":/images/cob.png").transformed(transform));
}

void Cob::advance(int step)
{
    qDebug()<<"come in Cob::advance";
    if (!step)
        return;
    if (up)
        setPos(mapToParent(0,-8));
    else
        setPos(mapToParent(0,8));
    if (pos().x()==target.x() && pos().y()>= target.y()-162+GRID_Y/2){
        qDebug()<<"before explode";
        emit explode(this);
        qDebug()<<"after explode";
        qDebug()<<"up is "<<up;
    }
    qDebug()<<"leave Cob::advance";
}

void Cob::pause()
{
    // qDebug()<<"come to Cob::pause";
    if (up)
        timer->pause();
}

void Cob::restore()
{
    // qDebug()<<"come to Cob::restore";
    if (up)
        timer->restore();
}

void Cob::reverse()
{
    up = false;
    setPos(target.x(),pos().y());
}

QPoint Cob::getTarget()
{
    return target;
}
