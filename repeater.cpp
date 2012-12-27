#include "repeater.h"

Repeater::Repeater(QObject *parent) :
    Plant("repeater")
{
    strength = 1;
    property = 1;
    counter = 0;
}

void Repeater::seeZombie(int row, int col)
{
    if (row == myRow && col > myCol && !hasZombie)
        hasZombie = true;
}

void Repeater::sendPea()
{
    if (hasZombie){
        if (counter == 0 || counter == 2)
           emit emitPea(myRow, myCol, strength, property);
        counter = counter >=25? 0:counter+1;
        hasZombie = false;
    }
}
