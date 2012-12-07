#include "QDebug"
#include "allzombies.h"
#include "plant.h"
#include "Constants.h"

AllZombies::AllZombies(QWidget *parent) :
    QWidget(parent),counter(0)
{
    timer = new QTimer(this);// timer for emitting zombies on the lawn
    connect(timer, SIGNAL(timeout()), this, SLOT(sendZombies()));
    timer->start(5000);
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

}

void AllZombies::addZombie(int row, int type)
{
    if (!type)
        qDebug()<<"unknown type of zombie!";
    Zombie* z = new Zombie();
    connect(z,SIGNAL(die(Zombie*)),this,SLOT(killDead(Zombie*)));
    connect(this,SIGNAL(receiveHit(Zombie*,int,int)),z,SLOT(hitten(Zombie*,int,int)),Qt::QueuedConnection);
    zombieList[row].push_back(z);
    // qDebug()<<"come to AllZombies::addZombie";
    emit addZombieAt(z,row,MAX_COL);
}

void AllZombies::countZombies()
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

bool AllZombies::zombieAt(int row, int col) const
{
    // qDebug()<<"come to AllZombies::zombieAt";
    QLinkedList<Zombie* >::const_iterator iter;
    for (iter = zombieList[row].constBegin(); iter!=zombieList[row].constEnd();++iter){
        // qDebug()<<row<<" "<<zombieList[row].size();
        /*
        qDebug()<<"come to zombieAt";
        qDebug()<<(int)((*iter)->pos().x()/GRID_X);
        */
        if ((int)((*iter)->pos().x()/GRID_X) == col)
            return true;
    }
    return false;
}

void AllZombies::killDead(Zombie* z)
{
    int row;
    // qDebug()<<"come to AllZombies::killDead first line";
    row = z->pos().y()/GRID_Y;
    QLinkedList<Zombie *>::iterator it = qFind(zombieList[row].begin(),
                                               zombieList[row].end(), z);
    // qDebug()<<"come to AllZombies::killDead";
    emit deleteZombie(z);
    if (it != zombieList[row].end())
        zombieList[row].erase(it);
    // qDebug()<<zombieList[row].size();
    // qDebug()<<"come to AllZombies::killDead after delete";
}

void AllZombies::sendZombies()
{
    counter++;
    int row =(qrand() % (ROW_NUMBER)) + 0;
    int type=1;
    // int type = (qrand() % (ZOMBIE_TYPE_NUMBER))+0;
    addZombie(row,type);
}

void AllZombies::clearRow(int row)
{
    // qDebug()<<"come to AllZombies::clearRow; "<<zombieList[row].size();
    QLinkedList<Zombie* >::const_iterator iter;
    // int number = zombieList[row].size();
    iter = zombieList[row].constBegin();
    for (int i = zombieList[row].size(); i>0; ++iter,--i){
        // qDebug()<<"come to AllZombies::clearRow before emittint";
        // qDebug()<<(*iter)->type();
        emit receiveHit(*iter,200,2);
    }
    // qDebug()<<"end allZombies::clearRow";
}
