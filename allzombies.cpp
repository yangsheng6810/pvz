#include "QDebug"
#include "allzombies.h"
#include "plant.h"
#include "Constants.h"

AllZombies::AllZombies(QWidget *parent) :
    QWidget(parent)
{
    // timer = new QTimer(this);// timer for emitting zombies on the lawn
    // connect(timer, SIGNAL(timeout()), this, SLOT(sendMessage()));
    // timer->start(1000);

}

void AllZombies::addZombie(int row, int type)
{
    if (!type)
        qDebug()<<"unknown type of zombie!";
    Zombie* z = new Zombie();
    zombiePack zp;
    zp.zombie = z;
    zp.row = row;
    zp.col = MAX_COL-1;
    zombieList[row].push_back(zp);
    qDebug()<<"here visited!";
    emit addZombieAt(z,zp.row,zp.col);
}

void AllZombies::sendMessage()
{
    // QLinkedList<zombiePack>::iterator i;
    // Plant* pp;
    // for (i = zombieList.begin(); i != zombieList.end(); ++i){
        // need other functions, and
        /*
        pp = plantAt(i->row,i->col);
        if (pp)
            eatPlant(pp);
        else
            i->zombie->stepForward();
        */
        // emit zombieAt(i->row,i->col);
    // }
}

bool AllZombies::zombieAt(int row, int col)
{
    QLinkedList<zombiePack>::iterator iter;
    for (iter = zombieList[row].begin(); iter!=zombieList[row].end();++iter)
        if (iter->col == col)
            return true;
    return false;
}
void AllZombies::peaShoot(int row, int colFrom, int strength)
{
    int minCol=100000;
    QLinkedList<zombiePack>::iterator i;
    Zombie* zombieHitten;
    for (i = zombieList[row].begin(); i != zombieList[row].end(); ++i){
        if (i->col >= colFrom && i->col < minCol){
            minCol = i->col;
            zombieHitten = i->zombie;
        }
    }
    if (zombieHitten)
        zombieHitten->hitten(PEA_HIT);
}

void AllZombies::reversePeaShoot(int row, int colFrom, int strength)
{
    int maxCol=0;
    QLinkedList<zombiePack>::iterator i;
    Zombie* zombieHitten;
    for (i = zombieList[row].begin(); i != zombieList[row].end(); ++i){
        if (i->col <= colFrom && i->col > maxCol){
            maxCol = i->col;
            zombieHitten = i->zombie;
        }
    }
    if (zombieHitten)
        zombieHitten->hitten(PEA_HIT);
}// implemented simply for split repeater
