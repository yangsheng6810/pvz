#include <QLabel>
#include <QMovie>
#include <QVBoxLayout>
#include <QTimer>
#include "zombie.h"
#include "Constants.h"

Zombie::Zombie(QWidget *parent, QString name) :
    QWidget(parent), zombieName(name),healthPoint(100),isFrozen(false)
{
    QLabel *zombie = new QLabel(this);
    QMovie *movie = new QMovie(":/images/"+name+".gif");
    zombie->setMovie(movie);
    movie->start();
    zombie->show();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(zombie);
    this->setLayout(layout);
}

void Zombie::hitten(int hitNumber)
{
    healthPoint -= hitNumber;
    if (healthPoint < 0)
        emit die(this);
}
void Zombie::freeze(int time)// to be implemented
{
    isFrozen += 1;
    QTimer::singleShot(FROZEN_TIME,this,SLOT(unfreeze()));
}
// void loseMetal(); this may be implemeted in individual zombies

void Zombie::unfreeze()
{
    isFrozen -= 1;
}

