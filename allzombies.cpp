#include "allzombies.h"
#include "QDebug"
#include "plant.h"
#include "Constants.h"
#include "coneheadzombie.h"
#include "bucketheadzombie.h"

AllZombies::AllZombies(QWidget *parent) :
    QWidget(parent),counter(0)
{
    timer = new Timer();// timer for emitting zombies on the lawn
    connect(timer, SIGNAL(timeout()), this, SLOT(sendZombies()));
    timer->start(5);
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

}

void AllZombies::restart()
{
    QLinkedList<Zombie*>::const_iterator iter;
    for (int i=0; i < ROW_NUMBER; i++){
        iter = zombieList[i].constBegin();
        for (int j = zombieList[i].size(); j>0; ++iter,--j){
            //(*iter)->deleteLater();
        }
        zombieList[i].clear();
    }
    timer->start();
}

void AllZombies::pause()
{
    emit pauseAllZombies();
    timer->pause();
}

void AllZombies::restore()
{
    emit restoreAllZombies();
    timer->restore();
}

void AllZombies::setField(Field* ff)
{
    f=ff;
}

void AllZombies::addZombie(int row, int type)
{
    if (!type)
        qDebug()<<"unknown type of zombie!";
    Zombie* z;
    switch(type){
        case 1:
            z =new Zombie(f);
            break;
        case 2:
            z = new ConeheadZombie(f);
            break;
        case 3:
            z = new BucketheadZombie(f);
            break;
        default:
            z = new Zombie(f);
    }
    connect(z,SIGNAL(die(Zombie*)),this,SLOT(killDead(Zombie*)));
    connect(this,SIGNAL(receiveHit(Zombie*,int,int)),z,SLOT(hitten(Zombie*,int,int)),Qt::QueuedConnection);
    connect(this,SIGNAL(pauseAllZombies()),z,SLOT(pause()));
    connect(this,SIGNAL(restoreAllZombies()),z,SLOT(restore()));
    connect(z,SIGNAL(youLose()),this,SIGNAL(youLose()));
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
    z->deleteLater();
}

void AllZombies::sendZombies()
{
    counter++;
    int row =(qrand() % (ROW_NUMBER)) + 0;
    // int row = 3;
       // qDebug()<<qrand();
    // int type=1;
    int type = (qrand() % 3)+1;
    addZombie(row,type);
    // addZombie(ROW_NUMBER-1,type);
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
        emit receiveHit(*iter,90,2);
    }
    // qDebug()<<"end allZombies::clearRow";
}

void AllZombies::clearBox(int row, int col)
{
    // qDebug()<<"row is "<<row<<", col is "<<col;
    QLinkedList<Zombie*>::const_iterator iter;
    iter = zombieList[row].constBegin();
    int currentRow=row;
    for (int i = zombieList[currentRow].size(); i>0; ++iter,--i){
        // qDebug()<<(*iter)->pos();
        // qDebug()<<(int)((*iter)->pos().x()/GRID_X);
        if (qAbs((int)((*iter)->pos().x()/GRID_X)-col)<=1){
            // qDebug()<<"kill";
            emit receiveHit(*iter,90,2);
        }
    }
    if (row >=1){
        currentRow = row-1;
        iter = zombieList[currentRow].constBegin();
        for (int i = zombieList[currentRow].size(); i>0; ++iter,--i){
            // qDebug()<<(*iter)->pos();
            if (qAbs((int)((*iter)->pos().x()/GRID_X)-col)<=1){
                // qDebug()<<"kill";
                emit receiveHit(*iter,90,2);
            }
        }
    }
    if (row <ROW_NUMBER-1){
        currentRow = row+1;
        iter = zombieList[currentRow].constBegin();
        for (int i = zombieList[currentRow].size(); i>0; ++iter,--i){
            // qDebug()<<(*iter)->pos();
            if (qAbs((int)((*iter)->pos().x()/GRID_X)-col)<=1){
                // qDebug()<<"kill";
                emit receiveHit(*iter,90,2);
            }
        }
    }
}

void AllZombies::sendHitBox(int row, int col, int strength)
{
    // qDebug()<<"come to AllZombies::sendHitBox";
    QLinkedList<Zombie*>::const_iterator iter=zombieList[row].constBegin();
    for (int i = zombieList[row].size(); i>0; ++iter,--i){
        if ((int)((*iter)->pos().x()/GRID_X)==col)
            emit receiveHit(*iter,strength,1);
    }
}

