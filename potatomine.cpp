#include "potatomine.h"
#include <QDebug>

#define MINE_POTATO_CHARGE_TIME 5

PotatoMine::PotatoMine(QObject *parent) :
    Plant("potatoMine")
{
    prepare = false;
    hasZombie = false;
    counter = 10;
}

PotatoMine::~PotatoMine()
{
    timer->deleteLater();
}

void PotatoMine::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
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

void PotatoMine::explode()
{
    emit sendHitBox(myRow, myCol, 90);
    emit destroyMe(this);
}

void PotatoMine::ready()
{
    prepare = true;
}

void PotatoMine::setPlanted()
{
    timer = new Timer(MINE_POTATO_CHARGE_TIME);
    connect(timer,SIGNAL(timeout()),this,SLOT(ready()));
    timer->setSingleShot();
    timer->start();
    planted = true;
}

void PotatoMine::pause()
{
    Plant::pause();
    timer->pause();
}

void PotatoMine::restore()
{
    Plant::restore();
    timer->restore();
}

void PotatoMine::seeZombie(int row, int col)
{
    if (row == myRow && col == myCol && prepare && !hasZombie)
        hasZombie = true;
}

void PotatoMine::sendPea()
{
    if (hasZombie){
        counter--;
        if (counter ==0)
            explode();
    }
}
