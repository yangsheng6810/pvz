#include <QDebug>
#include "plant.h"

Plant::Plant(QObject *parent, QString name) :
    QObject(parent), plantName(name), typeName("plant"),hasZombie(false), healthPoint(200)
{
    // setMinimumSize(40,40);
    // resetHealthPoint();
    movie = new QMovie(":/images/"+name+".gif");
    movie->start();
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

Plant::~Plant()
{
    delete(movie);
}

int Plant::type() const
{
    return Type;
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
    path.addRect(0, 0, 90, 100);
    return path;
}

void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //painter->drawPixmap(0,0,QPixmap(":/images/"+plantName+".gif"));
    // painter->drawPixmap(0,0,movie->currentPixmap());
    painter->drawImage(0,0,movie->currentImage());
    // painter->drawRect(0,0,90,100);
}

void Plant::advance(int step)
{
    if (!step)
        return;

    update();
    // setPos(mapToParent(-1, 0));
}

void Plant::setPlanted()
{
    planted = true;
}

void Plant::bitten(Plant* pp, int num)
{
    if (pp != this)
        return;
    healthPoint -= num;
    //if (healthPoint > 100)
    //    qDebug()<<"find wallNut";
    // qDebug()<<"hp now "<<healthPoint;
    emit hpChanged(healthPoint);
    if (healthPoint <= 0){
        emit destroyMe(this);
    }
}


/*
void Plant::resetHealthPoint()
{
    healthPoint = originHealthPoint;
    emit hpChanged(healthPoint);
}
*/

void Plant::setLocation(int row, int col)
{
    myRow = row;
    myCol = col;
}

void Plant::seeZombie(int row, int col)
{
    // qDebug()<<"comes to seeZombie in plant";
}

void Plant::sendPea()
{
}

void Plant::mousePressEvent(QMouseEvent *event)
{
    // qDebug()<<"visit Plant mouse event!";
}
