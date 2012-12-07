#include "jalapeno.h"
#include <QDebug>

Jalapeno::Jalapeno(QObject *parent) :
    Plant(parent ,"jalapeno")
{
}

void Jalapeno::explode()
{
    emit clearRow(myRow);
    emit destroyMe(this);
    // deleteLater();
    // qDebug()<<"come to Jalapeno::explode";
}

void Jalapeno::setPlanted()
{
    QTimer::singleShot(5000,this,SLOT(explode()));
    planted = true;
}
