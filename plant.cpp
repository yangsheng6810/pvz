#include "plant.h"

Plant::Plant(QWidget *parent) :
    QWidget(parent), healthPoint(100)
{
    setMinimumSize(40,40);
    QLabel *pea = new QLabel(this);
    QMovie *peaMovie = new QMovie(":/img/pea.png");
    pea->setMovie(peaMovie);
    pea->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    pea->setText(tr("a Pea"));
    // pea->move(20,20);
    pea->show();
    // pea->setAttribute(Qt::WA_DeleteOnClose);
    QPushButton *button = new QPushButton(tr("plant"));
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(pea);
    layout->addWidget(button);
    this->setLayout(layout);
}

void Plant::bitten(int num)
{
    healthPoint -= num;
    if (healthPoint <= 0){
        die();
    }
}

void Plant::die()
{
}
