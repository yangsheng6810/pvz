#include "threepeater.h"
#include "Constants.h"

Threepeater::Threepeater(QObject *parent) :
    Plant("threepeater"), strength(1), property(1),counter(0)
{
}

void Threepeater::seeZombie(int row, int col)
{
    // qDebug()<<"come to seeZombie in peashooter";
    if (row == myRow && col > myCol && !hasZombie)
        hasZombie = true;
    if (row == myRow-1 && col > myCol && !hasZombie)
        hasZombie = true;
    if (row == myRow+1 && col > myCol && !hasZombie)
        hasZombie = true;
    // qDebug()<<hasZombie;
}

void Threepeater::sendPea()
{
// qDebug()<<"come to sendPea in peashooter";
// qDebug()<<"row "<<myRow<<" col "<<myCol;
    if (hasZombie){
        if (counter == 0){
            emit emitPea(myRow, myCol, strength, property);
            if (myRow>=1)
                emit emitPea(myRow-1,myCol,strength,property);
            if (myRow<ROW_NUMBER-1)
                emit emitPea(myRow+1,myCol,strength,property);
        }
        counter = counter >= 25? 0:counter+1;
        hasZombie = false;
    }
}

QRectF Threepeater::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  190 + adjust, 180 + adjust);
}

