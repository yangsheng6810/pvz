#include <QTimer>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QDebug>
#include "plantcard.h"
#include "peashooter.h"
#include "sunflower.h"
#include "wallnut.h"
#include "snowpea.h"
#include "splitpea.h"
#include "threepeater.h"
#include "jalapeno.h"

PlantCard::PlantCard(QString plantName, int sun, int time, SunLight *parent) :
    name(plantName),theSun(parent), sunNeeded(sun), rechargeTime(time), sufficientSun(parent->sufficientSunLight(sun))
{
    connect(parent,SIGNAL(updateSun(int)),this,SLOT(sunUpdate(int)));
    layout = new QVBoxLayout;

    pixmap = new QPixmap(":/card/"+name+".png");
    button = new QPushButton;
    button->setIcon(QIcon(*pixmap));
    if (!sufficientSun)
        button->setEnabled(false);
    button->setIconSize(pixmap->rect().size());
    connect(button,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    layout->addWidget(button);

    bar = new QProgressBar;
    bar->setMinimum(0);
    bar->setMaximum(rechargeTime);
    bar->setValue(rechargeTime);
    layout->addWidget(bar);

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(charging()));

    waiting = 0;

    setLayout(layout);
}

PlantCard::~PlantCard()
{
    delete(pixmap);
    delete(button);
    delete(timer);
    delete(bar);
    delete(layout);
}

void PlantCard::recharge(void)
{
    button->setEnabled(false);
    waiting = rechargeTime;
    bar->setValue(rechargeTime-waiting);
    timer->start(200);
}

void PlantCard::charging(void)
{
    waiting--;
    bar->setValue(rechargeTime-waiting);
    if (!waiting){
        timer->stop();
        if (sufficientSun)
            button->setEnabled(true);
    }
}

void PlantCard::buttonEnable(void)
{
    button->setEnabled(true);
}

void PlantCard::sunUpdate(int num)
{
    // qDebug()<<"come to sunUpdate";
    if (num>= sunNeeded)
        sufficientSun=true;
    else
        sufficientSun=false;
    if (!button->isEnabled() && !waiting && sufficientSun )
        button->setEnabled(true);
    if (button->isEnabled() && !sufficientSun)
        button->setEnabled(false);
}

void PlantCard::buttonClicked(void)
{
    if (name=="peashooter"){
        PeaShooter* pea = new PeaShooter();
        emit tryPlanting(pea,this);
    }
    else if (name=="sunflower"){
        SunFlower* flower = new SunFlower();
        emit tryPlanting(flower,this);
    }
    else if (name=="wallNut"){
        WallNut* wallNut = new WallNut();
        emit tryPlanting(wallNut,this);
    }
    else if (name=="snowPea"){
        SnowPea* snowPea = new SnowPea();
        emit tryPlanting(snowPea,this);
    }
    else if (name=="splitPea"){
        SplitPea* splitPea = new SplitPea();
        emit tryPlanting(splitPea,this);
    }
    else if (name=="threepeater"){
        Threepeater* threepeater = new Threepeater();
        emit tryPlanting(threepeater,this);
    }
    else if (name=="jalapeno"){
        Jalapeno* jalapeno = new Jalapeno();
        emit tryPlanting(jalapeno,this);
    }
    else
        qDebug()<<"Wrong Name!";
}
int PlantCard::getSunNeeded()
{
    return sunNeeded;
}
