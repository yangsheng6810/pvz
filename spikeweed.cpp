#include "spikeweed.h"

Spikeweed::Spikeweed(QObject *parent) :
    Plant("spikeweed"),strength(1),counter(0)
{
    xShift= 10;
    yShift = 80;
}

void Spikeweed::seeZombie(int row, int col)
{
    if (row == myRow && col == myCol)
        hasZombie = true;
}

void Spikeweed::sendPea()
{
    if (hasZombie){
        if (counter == 0){
            emit sendHitBox(myRow, myCol,strength);
        }
        counter = counter >= 25? 0:counter+1;
        hasZombie = false;
    }
}

QRectF Spikeweed::boundingRect() const
{
    qreal adjust = 1;
    return QRectF( xShift- adjust,  yShift - adjust,
                  100 + adjust, 50 + adjust);
}
