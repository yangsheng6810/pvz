#include "kernelpult.h"

KernelPult::KernelPult(QObject *parent) :
    Plant("kernelPult"), strength(1), property(5), counter(0),tempCol(1000)
{
}

void KernelPult::seeZombie(int row, int col)
{
    if (row == myRow && col > myCol && col < tempCol && !hasZombie){
        hasZombie = true;
        tempCol = col;
    }
}

void KernelPult::sendPea()
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

QRectF KernelPult::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  190 + adjust, 180 + adjust);
}
