#include "peashooter.h"

PeaShooter::PeaShooter(QObject *parent) :
    Plant(), strength(1), property(1),counter(0)
{
}

void PeaShooter::seeZombie(int row, int col)
{
    // qDebug()<<"come to seeZombie in peashooter";
    if (row == myRow && col > myCol && !hasZombie)
        hasZombie = true;
    // qDebug()<<hasZombie;
}

void PeaShooter::sendPea()
{
    // qDebug()<<"come to sendPea in peashooter";
    // qDebug()<<"row "<<myRow<<" col "<<myCol;
    if (hasZombie){
        if (counter == 0){
            emit emitPea(myRow, myCol, strength, property);
        }
        counter = counter >= 25? 0:counter+1;
        hasZombie = false;
    }
}
