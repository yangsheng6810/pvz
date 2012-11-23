#include "plant.h"

Plant::Plant(QWidget *parent) :
    QWidget(parent), healthPoint(100)
{
    QPushButton *bite = new QPushButton(tr("bite"));
    connect(bite, SIGNAL(clicked()), this, SLOT(bitten()));
    hp = new QLCDNumber(3);
    hp->setSegmentStyle(QLCDNumber::Filled);
    connect(this,SIGNAL(hpChanged(int)),hp,SLOT(display(int)));
    setMinimumSize(40,40);
    QLabel *pea = new QLabel(this);
    pea->setPixmap(QPixmap(":/images/pea.png"));
    pea->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    pea->show();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(pea);
    layout->addWidget(bite);
    layout->addWidget(hp);
    this->setLayout(layout);
}

void Plant::bitten()
{
    int num = 4;
    healthPoint -= num;
    emit hpChanged(healthPoint);
    if (healthPoint <= 0){
        die();
    }
}

void Plant::die()
{
}
