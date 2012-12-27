#include "plantyard.h"

PlantYard::PlantYard(SunLight* mySun, Field* myField, QWidget *parent) :
    QWidget(parent),f(myField),sun(mySun)
{
    layout = new QHBoxLayout;
    addCard("peashooter",100,30);
    addCard("sunflower",50,15);
    addCard("wallNut",50,200);
    //addCard("snowPea",175,100);
    //addCard("splitPea",125,100);
    addCard("jalapeno",125,200);
    addCard("kernelPult",100,100);
    addCard("melonPult",300,100);
    addCard("threepeater",325,100);
    // addCard("cherryBomb",150,200);
    addCard("cobCannon",500,100);
    // addCard("spikeweed",100,100);
    // addCard("potatoMine",25,75);
    // addCard("tallNut",125,250);
    // addCard("squash",50,200);
    addCard("repeater",200,200);
    addCard("gatlingPea",250,200);
    addCard("torchwood",175,75);
    setLayout(layout);
}

void PlantYard::restart()
{
    emit restartAllCards();
    update();
}

void PlantYard::pause()
{
    emit pauseAllCards();
}

void PlantYard::restore()
{
    emit restoreAllCards();
}

void PlantYard::clear()
{
    delete(layout);
    layout = new QHBoxLayout;
    setLayout(layout);
    emit destroyAllCards();
}

void PlantYard::addCard(QString name,int cost, int time)
{
    // qDebug()<<"come to PlantYard::addCard with name "<<name;
    PlantCard* card = new PlantCard(name,cost,time,sun);
    connect(sun,SIGNAL(updateSun(int)),card,SLOT(sunUpdate(int)));
    connect(card,SIGNAL(tryPlanting(Plant*,PlantCard*)),f,SLOT(addPlant(Plant*,PlantCard*)));
    connect(this,SIGNAL(restartAllCards()),card,SLOT(restart()));
    connect(this,SIGNAL(pauseAllCards()),card,SLOT(pause()));
    connect(this,SIGNAL(restoreAllCards()),card,SLOT(restore()));
    connect(this,SIGNAL(destroyAllCards()),card,SLOT(destroyMe()));
    layout->addWidget(card);
}
