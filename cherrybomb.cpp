#include "cherrybomb.h"
#include <QDebug>

#define CHERRY_BOMB_EXPLODE_TIME 1.2

CherryBomb::CherryBomb(QObject *parent) :
    Plant("cherryBomb")
{
}

CherryBomb::~CherryBomb()
{
    timer->deleteLater();
}

void CherryBomb::explode()
{
    emit clearBox(myRow, myCol);
    // qDebug()<<"come to CherryBomb::explode()";
    emit destroyMe(this);
}


void CherryBomb::setPlanted()
{
    // QTimer::singleShot(CHERRY_BOMB_EXPLODE_TIME*1000,this,SLOT(explode()));
    timer = new Timer(CHERRY_BOMB_EXPLODE_TIME);
    connect(timer,SIGNAL(timeout()),this,SLOT(explode()));
    timer->setSingleShot();
    timer->start();
    planted = true;
}

void CherryBomb::pause()
{
    Plant::pause();
    timer->pause();
}

void CherryBomb::restore()
{
    Plant::restore();
    timer->restore();
}
