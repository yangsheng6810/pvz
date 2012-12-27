#include "sunlight.h"
#include <QDebug>
// #include "timer.h"

SunLight::SunLight(QWidget *parent) :
    QWidget(parent),sunLight(1000)
{
    lcd = new QLCDNumber(4);// for debug
    connect(this,SIGNAL(updateSun(int)),lcd,SLOT(display(int)));
    QPushButton* button = new QPushButton(tr("add sunlight"));
    // QPushButton* button1 = new QPushButton(tr("pause"));
    // QPushButton* button2 = new QPushButton(tr("restore"));
    connect(button, SIGNAL(clicked()),this,SLOT(addSunLight()));
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(lcd);
    layout->addWidget(button);
    // layout->addWidget(button1);
    // layout->addWidget(button2);
    addSunLight(0);// dirty code
    this->setLayout(layout);
    // Timer* timer = new Timer(10);
    // connect(timer,SIGNAL(timeout()),this,SLOT(addSunLight()));
    // connect(button1,SIGNAL(clicked()),timer,SLOT(pause()));
    // connect(button2,SIGNAL(clicked()),timer,SLOT(restore()));
    // timer->start();
}

void SunLight::restart()
{
    sunLight = 1000;
    emit updateSun(sunLight);
    paused = false;
}

void SunLight::pause()
{
    paused = true;
}

void SunLight::restore()
{
    paused = false;
}

void SunLight::addSunLight(int num)
{
    sunLight += num;
    if (sunLight > 9990)
        sunLight = 9990;
    emit updateSun(sunLight);
}

void SunLight::addSunLight()// for debug
{
    if (paused)
        return;
    sunLight += 25;
    if (sunLight > 9990)
        sunLight = 9990;
    emit updateSun(sunLight);
}

bool SunLight::sufficientSunLight(int num)
{
    if (num <= sunLight)
        return true;
    else
        return false;
}

void SunLight::subtractSunLight(int num)
{
    sunLight -= num;
    emit updateSun(sunLight);
}
