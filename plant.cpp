#include "plant.h"

int Plant::originHealthPoint = 100;

Plant::Plant(QWidget *parent, QString picName) :
    QWidget(parent)  //, healthPoint(originHealthPoint)
{
    QPushButton *bite = new QPushButton(tr("bite"));
    connect(bite, SIGNAL(clicked()), this, SLOT(bitten()));// this is for debug

    hp = new QLCDNumber(3);
    hp->setSegmentStyle(QLCDNumber::Filled);
    connect(this,SIGNAL(hpChanged(int)),hp,SLOT(display(int)));

    setMinimumSize(40,40);
    resetHealthPoint();

    QLabel *pea = new QLabel(this);
    QMovie *movie = new QMovie(picName);
    pea->setMovie(movie);
    movie->start();
    pea->show();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(pea);
    layout->addWidget(bite);
    layout->addWidget(hp);
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
