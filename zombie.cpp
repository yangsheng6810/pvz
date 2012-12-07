#include <QLabel>
#include <QMovie>
#include <QVBoxLayout>
#include <QTimer>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QPixmap>
#include <QTimer>
#include <QDebug>
#include "zombie.h"
#include "Constants.h"

Zombie::Zombie(QObject *parent, QString name) :
    QObject(parent), zombieName(name),typeName("zombie"), healthPoint(100),isFrozen(0),whichStep(0)
{
    eating = true;
    plant = NULL;
    movie = new QMovie(":/images/"+name+".gif");
    movie->start();
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
    setZValue(5);
    QTimer* timer = new QTimer;
    QObject::connect(timer,SIGNAL(timeout()), this, SLOT(tryEating()));
    timer->start(1000);
}

Zombie::~Zombie()
{
    delete(movie);
}

int Zombie::type() const
{
    return Type;
}

QRectF Zombie::boundingRect() const
{
    qreal adjust = 5;
    return QRectF( 0- adjust, 0 - adjust,
                  90 + adjust, 130 + adjust);
}

QPainterPath Zombie::shape() const
{
    QPainterPath path;
    qreal adjust = -5;
    path.addRect(0 - adjust, 0 - adjust, 90 + adjust, 130 + adjust);
    return path;
}

void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // painter->drawPixmap(0,0,QPixmap(":/images/"+zombieName+".gif"));
    painter->drawImage(0,0,movie->currentImage());
    // qreal adjust = 0.5;
    // painter->drawRect(0,0,182,173);
}

void Zombie::advance(int step)
{
    if (!step)
        return;
    list = collidingItems();
    Plant* pp;
    for (int i=0; i< list.size(); ++i){
        pp = qgraphicsitem_cast<Plant*>(list.at(i));
        if (pp){
            // qDebug()<<"find plant";
            eating = true;
            plant = pp;
            // emit sendEat(pp, 10);
            update();
            return;
        }
        else{
            plant = NULL;
            eating = false;
        }
    }
    if (((whichStep % 6==0) && !isFrozen )|| (whichStep % 20==0)){
        setPos(mapToParent(-1,0));
    }
    whichStep = whichStep > 0? whichStep-1: 100;
    update();
}

void Zombie::hitten(Zombie* z, int hitNumber, int property)
{
    // qDebug()<<"come to Zombie::hitten";
    if (z != this)
        return;
    // qDebug()<<"come to Zombie::hitten "<<hitNumber;
    healthPoint -= hitNumber;
    // qDebug()<<"current healthPoint "<<healthPoint;
    if (property == 3)
        freeze();
    if (healthPoint <= 0){
        emit die(this);
        deleteLater();
    }
}
void Zombie::freeze()// to be implemented
{
    isFrozen += 1;
    QTimer::singleShot(FROZEN_TIME*1000,this,SLOT(unfreeze()));
}
// void loseMetal(); this may be implemeted in individual zombies

void Zombie::unfreeze()
{
    isFrozen -= 1;
}

void Zombie::tryEating()
{
    if (eating){
        // qDebug()<<(plant != NULL);
        emit sendEat(plant,10);
    }
}


