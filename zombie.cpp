#include <QLabel>
#include <QMovie>
#include <QVBoxLayout>
#include <QTimer>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QPixmap>
#include "zombie.h"
#include "Constants.h"

Zombie::Zombie(QObject *parent, QString name) :
    QObject(parent), zombieName(name),healthPoint(100),isFrozen(false)
{
    /*
    QLabel *zombie = new QLabel(this);
    QMovie *movie = new QMovie(":/images/"+name+".gif");
    zombie->setMovie(movie);
    movie->start();
    zombie->show();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(zombie);
    this->setLayout(layout);
    */
}
QRectF Zombie::boundingRect() const
{
    qreal adjust = 5;
    return QRectF(-18 - adjust, -22 - adjust,
                  250 + adjust, 290 + adjust);
}

QPainterPath Zombie::shape() const
{
    QPainterPath path;
    path.addRect(-20, -20, 50, 140);
    return path;
}

void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(-20,0,QPixmap(":/images/"+zombieName+".gif"));
}

void Zombie::advance(int step)
{
    if (!step)
        return;

    setPos(mapToParent(0,0));
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

