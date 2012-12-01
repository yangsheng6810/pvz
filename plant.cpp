#include "plant.h"

int Plant::originHealthPoint = 100;

Plant::Plant(QWidget *parent, QString name) :
    QWidget(parent), plantName(name)  //, healthPoint(originHealthPoint)
{
    // the following are for debug
    /*
    QPushButton *bite = new QPushButton(tr("bite"));
    connect(bite, SIGNAL(clicked()), this, SLOT(bitten()));// this is for debug

    hp = new QLCDNumber(3);
    hp->setSegmentStyle(QLCDNumber::Filled);
    connect(this,SIGNAL(hpChanged(int)),hp,SLOT(display(int)));
    */

    setMinimumSize(40,40);
    resetHealthPoint();

    QLabel *plant = new QLabel(this);
    QMovie *movie = new QMovie(":/images/"+name+".gif");
    plant->setMovie(movie);
    movie->start();
    plant->show();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(plant);
    // the following are for debug
    /*
    layout->addWidget(bite);
    layout->addWidget(hp);
    */
    this->setLayout(layout);
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
