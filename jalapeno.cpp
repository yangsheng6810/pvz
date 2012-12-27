#include "jalapeno.h"
#include <QDebug>
#define JALAPENO_EXPLODE_TIME 1.5

Jalapeno::Jalapeno(QObject *parent) :
    Plant("jalapeno")
{
}

Jalapeno::~Jalapeno()
{
    timer->deleteLater();
}

void Jalapeno::pause()
{
    Plant::pause();
    timer->pause();
}

void Jalapeno::restore()
{
    Plant::restore();
    timer->restore();
}

void Jalapeno::explode()
{
    emit clearRow(myRow);
    emit destroyMe(this);
    deleteLater();
    // qDebug()<<"come to Jalapeno::explode";
}

void Jalapeno::setPlanted()
{
    //QTimer::singleShot(JALAPENO_EXPLODE_TIME*1000,this,SLOT(explode()));
    timer = new Timer(JALAPENO_EXPLODE_TIME);
    connect(timer,SIGNAL(timeout()),this,SLOT(explode()));
    timer->setSingleShot();
    timer->start();
    planted = true;
}
