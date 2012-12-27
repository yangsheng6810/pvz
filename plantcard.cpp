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
#include "kernelpult.h"
#include "melonpult.h"
#include "cherrybomb.h"
#include "cobcannon.h"
#include "spikeweed.h"
#include "potatomine.h"
#include "tallnut.h"
#include "squash.h"
#include "repeater.h"
#include "gatlingpea.h"
#include "torchwood.h"

PlantCard::PlantCard(QString plantName, int sun, int time, SunLight *parent) :
    name(plantName),sunNeeded(sun),rechargeTime(time),theSun(parent), sufficientSun(parent->sufficientSunLight(sun))
{
    sufficientSun = parent->sufficientSunLight(sun);
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

    timer = new Timer();
    connect(timer,SIGNAL(timeout()),this,SLOT(charging()));

    waiting = 0;

    setLayout(layout);
    paused = false;
}


PlantCard::~PlantCard()
{
    delete(pixmap);
    delete(button);
    delete(timer);
    delete(bar);
    delete(layout);
}

void PlantCard::restart()
{
    waiting = 0;
    button->setEnabled(true);
    bar->setValue(rechargeTime);
    timer->stop();
}

void PlantCard::pause()
{
    timer->pause();
    paused = true;
}

void PlantCard::restore()
{
    timer->restore();
    paused = false;
}

void PlantCard::destroyMe()
{
    deleteLater();
}

void PlantCard::recharge(void)
{
    button->setEnabled(false);
    waiting = rechargeTime;
    bar->setValue(rechargeTime-waiting);
    timer->start(0.2);
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
    if (paused)
        return;
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
    else if (name=="kernelPult"){
        KernelPult* kernelPult = new KernelPult();
        emit tryPlanting(kernelPult, this);
    }
    else if (name=="melonPult"){
        MelonPult* melonPult = new MelonPult();
        emit tryPlanting(melonPult,this);
    }
    else if (name=="cherryBomb"){
        CherryBomb* cherryBomb = new CherryBomb();
        emit tryPlanting(cherryBomb,this);
    }
    else if (name=="cobCannon"){
        CobCannon* cobCannon = new CobCannon();
        emit tryPlanting(cobCannon,this);
    }
    else if (name=="spikeweed"){
        Spikeweed* spikeweed = new Spikeweed();
        emit tryPlanting(spikeweed, this);
    }
    else if (name=="potatoMine"){
        PotatoMine* potatoMine = new PotatoMine();
        emit tryPlanting(potatoMine, this);
    }
    else if (name=="tallNut"){
        TallNut* tallNut = new TallNut();
        emit tryPlanting(tallNut,this);
    }
    else if (name=="squash"){
        Squash* squash = new Squash();
        emit tryPlanting(squash,this);
    }
    else if (name=="repeater"){
        Repeater* repeater = new Repeater();
        emit tryPlanting(repeater,this);
    }
    else if (name=="gatlingPea"){
        GatlingPea* gatlingPea = new GatlingPea();
        emit tryPlanting(gatlingPea,this);
    }
    else if (name=="torchwood"){
        Torchwood* torchwood = new Torchwood();
        emit tryPlanting(torchwood, this);
    }
    else
        qDebug()<<"Wrong Name!";
}
int PlantCard::getSunNeeded()
{
    return sunNeeded;
}
