#include "gatlingpea.h"

GatlingPea::GatlingPea(QObject *parent) :
    Plant("gatlingPea")
{
    strength = 1;
    property = 1;
    counter = 0;
}

void GatlingPea::seeZombie(int row, int col)
{
    if (row == myRow && col > myCol && !hasZombie)
        hasZombie = true;
}

void GatlingPea::sendPea()
{
    if (hasZombie){
        if (counter == 0 || counter == 2 || counter == 4 || counter ==6)
           emit emitPea(myRow, myCol, strength, property);
        counter = counter >=25? 0:counter+1;
        hasZombie = false;
    }
}
