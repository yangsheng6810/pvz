#include "sunflower.h"
#include "sunlight.h"

SunFlower::SunFlower(QObject *parent):
Plant(parent, "sunflower")
{
    QTimer *timer = new QTimer(this);// timer for emitting sun light
    connect(timer, SIGNAL(timeout()), this, SLOT(sunLight()));
    timer->start(10000);
}

void SunFlower::sunLight()
{
    emit produceSunLight(50);
}
