#include "melonpult.h"

MelonPult::MelonPult(QObject *parent) :
Plant("melonPult"), strength(4), property(6), counter(0),tempCol(1000)
{
}

void MelonPult::seeZombie(int row, int col)
{
if (row == myRow && col > myCol && col < tempCol && !hasZombie){
    hasZombie = true;
    tempCol = col;
}
}

void MelonPult::sendPea()
{
if (hasZombie){
    if (counter == 0){
        emit emitPea(myRow, myCol, strength, property, tempCol-myCol+1);
    }
    counter = counter >= 25? 0:counter+1;
    hasZombie = false;
    tempCol = 1000;
}
}

QRectF MelonPult::boundingRect() const
{
qreal adjust = 0.5;
return QRectF(-18 - adjust, -22 - adjust,
              190 + adjust, 180 + adjust);
}
