#include "sunflower.h"
#include "sunlight.h"

SunFlower::SunFlower(QWidget *parent):
Plant(parent, ":/images/sunflower.gif")
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(sunLight()));
    timer->start(1000);
}

void SunFlower::sunLight()
{
    emit produceSunLight(50);
}
