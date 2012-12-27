#include "pea.h"
#include "plant.h"
#include "zombie.h"
#include "Constants.h"
#include <cmath>

Pea::Pea(int Strength, int Property, int row, QString name, int targetCol) :
    peaName(name), typeName("pea"),property(Property),strength(Strength),tCol(targetCol),myRow(row)
{
    whichStep = 0;
    setZValue(10);
    if (property >= 5)
        ySpeed = -20;
}

int Pea::type() const
{
    return Type;
}

QRectF Pea::boundingRect() const
{
    qreal adjust = 5;
    return QRectF(0 - adjust, 0 - adjust,
                  140 + adjust, 140 + adjust);
}

QPainterPath Pea::shape() const
{
    QPainterPath path;
    path.addRect(0,0,40,40);
    return path;
}

void Pea::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (property != 2)
        painter->drawPixmap(0,0,QPixmap(":/images/"+peaName+".png"));
    else
        painter->drawPixmap(0,0,QPixmap(":/images/firePea.png"));
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
    if (property >= 5){
        setPos(mapToParent(qreal(tCol*GRID_X-GRID_X/2)/100,ySpeed));
        // setRotation(rotation()+1);
        ySpeed += 0.4;
    }
    else if (property < 0)
        setPos(mapToParent(-4,0));
    else
        setPos(mapToParent(4,0));

    // do with collision with zombies
    list = collidingItems();
    Zombie* zz=NULL, *ztemp;
    bool succeed= false;
    bool thisSucceed;
    for (int i = 0; i < list.size(); ++i) {
        // qDebug()<<"come before cast to zombie*";
        ztemp = qgraphicsitem_cast<Zombie *>(list.at(i));
        thisSucceed = false;
        if (ztemp){
            if ((int)(ztemp->pos().y()/GRID_Y) == myRow){
                succeed = true;
                thisSucceed = true;
            }
        }

        if ( thisSucceed && (zz == NULL || ztemp->pos().x() < zz->pos().x())){
            // qDebug()<<"succeed or not? "<<succeed;
            zz = ztemp;
        }
    }
    if (succeed){
            emit sendHit(zz,strength, property);
            emit destroyMe(this);
            deleteLater();
    }
    // qDebug()<<"leave Pea::advance";
}

void Pea::setProperty(int newProperty)
{
    if (property == newProperty)
        return;
    property = newProperty;
}

int Pea::getProperty()
{
    return property;
}
