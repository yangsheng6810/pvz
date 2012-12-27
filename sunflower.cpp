#include "sunflower.h"
#include "sunlight.h"
#include <QDebug>

SunFlower::SunFlower(QObject *parent):
Plant("sunflower")
{
    timer = new Timer();// timer for emitting sun light
    connect(timer, SIGNAL(timeout()), this, SLOT(sunLight()));
    timer->start(24);
}

SunFlower::~SunFlower()
{
    timer->deleteLater();
}

void SunFlower::sunLight()
{
    emit produceSun(this);
    //emit produceSunLight(50);
}

void SunFlower::pause()
{
    Plant::pause();
    timer->pause();
}

void SunFlower::restore()
{
    Plant::restore();
    timer->restore();
}
