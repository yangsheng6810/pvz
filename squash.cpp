#include "squash.h"
#include "Constants.h"

Squash::Squash(QObject *parent) :
    Plant("squash")
{
    hasZombie = false;
    counter = 10;
    ySpeed = 40;
}

void Squash::seeZombie(int row, int col)
{
    if (row == myRow && col == myCol && !hasZombie)
        hasZombie = true;
}

void Squash::advance(int step)
{
    if (!step)
        return;
    if (hasZombie){
        setPos(mapToParent(5,-ySpeed));
        ySpeed -= 5;
    }
    update();
    if (pos().y() > myRow*GRID_Y){
        emit sendHitBox(myRow, myCol, 90);
        emit destroyMe(this);
    }
}
