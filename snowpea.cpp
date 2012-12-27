#include "snowpea.h"

SnowPea::SnowPea(QObject *parent):
    Plant("snowPea"), strength(1), property(3),counter(0)
{
}

void SnowPea::seeZombie(int row, int col)
{
    // qDebug()<<"come to seeZombie in peashooter";
    if (row == myRow && col > myCol && !hasZombie)
        hasZombie = true;
    // qDebug()<<hasZombie;
}

void SnowPea::sendPea()
{
    // qDebug()<<"come to sendPea in peashooter";
    // qDebug()<<"row "<<myRow<<" col "<<myCol;
    if (hasZombie){
        if (counter == 0){
            // qDebug()<<"come to sendPea in peashooter";
            emit emitPea(myRow, myCol, strength, property);
        }
        counter = counter >= 25? 0:counter+1;
        hasZombie = false;
    }
}
