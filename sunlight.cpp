#include "sunlight.h"

SunLight::SunLight(QWidget *parent) :
    QWidget(parent),sunLight(1000)
{
    lcd = new QLCDNumber(4);// for debug
    connect(this,SIGNAL(updateSun(int)),lcd,SLOT(display(int)));
    QPushButton* button = new QPushButton(tr("add sunlight"));
    connect(button, SIGNAL(clicked()),this,SLOT(addSunLight()));
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(lcd);
    layout->addWidget(button);
    addSunLight(0);// dirty code
    this->setLayout(layout);
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
    sunLight += 50;
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
