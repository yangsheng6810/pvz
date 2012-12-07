#include "splitpea.h"

SplitPea::SplitPea(QObject *parent) :
    Plant(parent, "splitPea"), strength(10), property(1),counter(0)
{
}

void SplitPea::seeZombie(int row, int col)
{
    // qDebug()<<"come to seeZombie in peashooter";
    if (row == myRow && !hasZombie)
        hasZombie = true;
    // qDebug()<<hasZombie;
}

void SplitPea::sendPea()
{
    // qDebug()<<"come to sendPea in peashooter";
    // qDebug()<<"row "<<myRow<<" col "<<myCol;
    if (hasZombie){
        if (counter == 0){
            emit emitPea(myRow, myCol, strength, property);
            emit emitPea(myRow, myCol, strength, -property);
        }
        counter = counter >= 5? 0:counter+1;
        hasZombie = false;
    }
}

QRectF SplitPea::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  190 + adjust, 180 + adjust);
}
