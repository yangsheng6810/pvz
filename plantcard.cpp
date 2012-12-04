#include <QTimer>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QDebug>
#include "plantcard.h"
#include "peashooter.h"
#include "sunflower.h"

PlantCard::PlantCard(QString plantName, int sun, int time, SunLight *parent) :
    theSun(parent), name(plantName), sunNeeded(sun), rechargeTime(time), sufficientSun(parent->sufficientSunLight(sun))
{
    connect(parent,SIGNAL(updateSun(int)),this,SLOT(sunUpdate(int)));
    QVBoxLayout* layout = new QVBoxLayout;

    QPixmap* pixmap = new QPixmap(":/card/"+name+".png");
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
    if (num>= sunNeeded)
        sufficientSun=true;
    else
        sufficientSun=false;
    if (!button->isEnabled() && !waiting && sufficientSun )
        button->setEnabled(true);
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
    else
        qDebug()<<"Wrong Name!";
}
