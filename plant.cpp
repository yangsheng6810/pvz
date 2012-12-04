#include "plant.h"

int Plant::originHealthPoint = 100;

Plant::Plant(QObject *parent, QString name) :
    QObject(parent), plantName(name)  //, healthPoint(originHealthPoint)
{
    // setMinimumSize(40,40);
    resetHealthPoint();
    /*
    QLabel *plant = new QLabel(this);
    QMovie *movie = new QMovie(":/images/"+name+".gif");
    plant->setMovie(movie);
    movie->start();
    plant->show();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(plant);
    */
    // the following are for debug
    /*
    layout->addWidget(bite);
    layout->addWidget(hp);
    */
    /*
    this->setLayout(layout);
    */

}
QRectF Plant::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  140 + adjust, 180 + adjust);
}

QPainterPath Plant::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 50, 140);
    return path;
}

void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0,0,QPixmap(":/images/"+plantName+".gif"));
}

void Plant::advance(int step)
{
    if (!step)
        return;

    // setPos(mapToParent(-1, 0));
}
void Plant::bitten()
{
    int num = 4;
    healthPoint -= num;
    emit hpChanged(healthPoint);
    if (healthPoint <= 0){
        die();
    }
}

void Plant::die()
{
}

void Plant::resetHealthPoint()
{
    healthPoint = originHealthPoint;
    emit hpChanged(healthPoint);
}
