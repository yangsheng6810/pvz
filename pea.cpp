#include "pea.h"
#include "plant.h"
#include "zombie.h"

Pea::Pea(int Strength, int Property, QString name) :
    peaName(name), typeName("pea"),property(Property),strength(Strength),whichStep(0)
{
    setZValue(10);
}

int Pea::type() const
{
    return Type;
}

QRectF Pea::boundingRect() const
{
    qreal adjust = 5;
    return QRectF(0 - adjust, 0 - adjust,
                  40 + adjust, 40 + adjust);
}

QPainterPath Pea::shape() const
{
    QPainterPath path;
    path.addRect(0,0,40,40);
    return path;
}

void Pea::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0,0,QPixmap(":/images/"+peaName+".png"));
}

void Pea::advance(int step)
{
    // qDebug()<<"come to Pea::advance";
    if (!step)
        return;
    /*
    if (!whichStep){
        setPos(mapToParent(2,0));
        whichStep = 2;
    }
    else
        whichStep--;
    */
    if (property < 0)
        setPos(mapToParent(-2,0));
    else
        setPos(mapToParent(2,0));

    // do with collision with zombies
    list = collidingItems();
    Zombie* zz;
    bool succeed= false;
    for (int i = 0; i < list.size(); ++i) {
        // qDebug()<<"come before cast to zombie*";
        zz = qgraphicsitem_cast<Zombie *>(list.at(i));
        // qDebug()<<"come after cast to zombie*";
        if (zz){
            succeed = true;
            break;
        }
    }
    if (succeed){
            emit sendHit(zz,strength, property);
            emit destroyMe(this);
    }
    // qDebug()<<"leave Pea::advance";
}
