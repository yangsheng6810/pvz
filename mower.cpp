#include "mower.h"
#include "Constants.h"

Mower::Mower(int row,QObject *parent) :
    myRow(row)
{
    // pic = new QPixmap(":/images/mower.png");
    running = false;
}

Mower::~Mower()
{
    // delete(pic);
}

int Mower::type() const
{
    return Type;
}

QRectF Mower::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-10- adjust, -10 - adjust,
                  140 + adjust, 100 + adjust);
}

QPainterPath Mower::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 100, 85);
    return path;
}

void Mower::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
   painter->drawImage(0,0,QImage(":/images/mower.png"));
}

void Mower::advance(int step)
{
    if (!step)
        return;
    QList<QGraphicsItem*> list = collidingItems();
    Zombie* zz = NULL;
    for (int i = 0; i< list.size(); ++i){
        zz = qgraphicsitem_cast<Zombie *>(list.at(i));
        if (zz && (int)zz->pos().y()/GRID_Y==myRow){
            emit sendHit(zz,1000,1);
            running = true;
        }
    }
    if (!running)
        return;
    setPos(mapToParent(10,0));
    if (pos().x()> 8*GRID_X){
        emit destroyMe(this);
        // emit clearLine(myRow);
        deleteLater();
    }
}
