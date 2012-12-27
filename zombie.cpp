#include <QLabel>
#include <QTimer>
#include <QPainter>
#include <QStyleOption>
#include <QPixmap>
#include <QTimer>
#include <QDebug>
#include "zombie.h"
#include "Constants.h"

Zombie::Zombie(Field* ff, QString name, QObject *parent) :
    zombieName(name),typeName("zombie"),f(ff),healthPoint(10),isFrozen(0),whichStep(0)
{
    xShift = 0;
    yShift = -10;
    eating = true;
    plant = NULL;
    movie = new QMovie(":/images/"+name+".gif");
    movie->start();
    dead = false;
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
    setZValue(5+qrand()%5);
    timer = new Timer();
    connect(timer,SIGNAL(timeout()), this, SLOT(tryEating()));
    timer->start(1);
    // qDebug()<<"Zombie at location "<<(long)this;
}

Zombie::~Zombie()
{
    delete(movie);
    delete(timer);
}

int Zombie::type() const
{
    return Type;
}

QRectF Zombie::boundingRect() const
{
    qreal adjust = 5;
    return QRectF( xShift - adjust, yShift - adjust,
                  90 + adjust, 130 + adjust);
}

QPainterPath Zombie::shape() const
{
    QPainterPath path;
    qreal adjust = -5;
    path.addRect(xShift - adjust, yShift - adjust, 90 + adjust, 130 + adjust);
    return path;
}

void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // painter->drawPixmap(0,0,QPixmap(":/images/"+zombieName+".gif"));
    painter->drawImage(xShift,yShift,movie->currentImage());
    // painter->drawPath(shape());
    // qreal adjust = 0.5;
    // painter->drawRect(0,0,182,173);
}

void Zombie::advance(int step)
{
    if (!step)
        return;
    // list = collidingItems();
    QPoint point(targetPoint(this->pos()));
    Plant* pp=f->getPlant(point.y(),point.x());
    if (pp && QString(pp->metaObject()->className())!="Spikeweed"){
        eating = true;
        plant = pp;
        update();
        return;
    }
    else{
        plant = NULL;
        eating = false;
    }
    /*
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
    */
    if (((whichStep % 6==0) && !isFrozen )|| (whichStep % 20==0)){
        setPos(mapToParent(-1,0));
    }
    whichStep = whichStep > 0? whichStep-1: 100;
    update();
    if (pos().x()<-GRID_X)
        emit youLose();
}

void Zombie::pause()
{
    movie->setPaused(true);
    timer->pause();
}

void Zombie::restore()
{
    movie->start();
    timer->restore();
}

void Zombie::hitten(Zombie* z, int hitNumber, int property)
{
    if (dead)
        return;
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
        dead = true;
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

const QPoint Zombie::targetPoint(const QPointF &position) const
{
    return QPoint((position.x()+GRID_X/2)/GRID_X, (position.y())/GRID_Y);
}


