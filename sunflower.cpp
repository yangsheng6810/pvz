#include "sunflower.h"
#include "sunlight.h"

SunFlower::SunFlower(QWidget *parent):
Plant(parent, "sunflower")
{
    QTimer *timer = new QTimer(this);// timer for emitting sun light
    connect(timer, SIGNAL(timeout()), this, SLOT(sunLight()));
    timer->start(1000);
}

void SunFlower::sunLight()
{
    emit produceSunLight(50);
}
