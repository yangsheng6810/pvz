#include "carddialog.h"
#include <QPushButton>
#include <QCheckBox>
#include <QDebug>

CardDialog::CardDialog(PlantYard* yy,QWidget *parent) :
    QDialog(parent),yard(yy)
{
    layout = new QGridLayout();
    row = 0;
    col = 0;
    counter = 0;
    mapper = new QSignalMapper(this);
    connect(mapper,SIGNAL(mapped(int)),this,SLOT(prepareCard(int)));
    addCard("peashooter",100,30);
    addCard("sunflower",50,15);
    addCard("wallNut",50,200);
    addCard("snowPea",175,100);
    addCard("splitPea",125,100);
    addCard("jalapeno",125,200);
    addCard("kernelPult",100,100);
    addCard("melonPult",300,100);
    addCard("threepeater",325,100);
    addCard("cherryBomb",150,200);
    addCard("cobCannon",500,100);
    addCard("spikeweed",100,100);
    addCard("potatoMine",25,75);
    addCard("tallNut",125,250);
    addCard("squash",50,200);
    addCard("repeater",200,200);
    addCard("gatlingPea",250,200);
    addCard("torchwood",175,75);

    QPushButton* ok = new QPushButton(tr("OK"));
    connect(ok,SIGNAL(clicked()),this,SLOT(okClicked()));
    QPushButton* cancel = new QPushButton(tr("Cancel"));
    connect(cancel,SIGNAL(clicked()),this,SLOT(cancelClicked()));
    layout->addWidget(ok,3,4);
    layout->addWidget(cancel,3,5);
    setLayout(layout);
    setWindowTitle(tr("Choose cards"));
}

void CardDialog::addCard(QString name, int newCost, int newTime)
{
    QCheckBox* card = new QCheckBox();
    QPixmap pixmap(":/card/"+name+".png");
    card->setIcon(QIcon(pixmap));
    card->setIconSize(pixmap.rect().size());
    card->setCheckable(true);
    card->setChecked(false);
    connect(card,SIGNAL(stateChanged(int)),mapper,SLOT(map()));
    mapper->setMapping(card,row*6+col);
    layout->addWidget(card,row,col);
    allName[row][col] = name;
    chosenName[row][col] = false;
    cost[row][col] = newCost;
    time[row][col] = newTime;
    col++;
    if (col == 6){
        col = 0;
        row++;
    }
}

void CardDialog::okClicked()
{
    if (counter != 10){
        QMessageBox::information(this,
                             tr("Inproper number"),
                             tr("You can use exactly 10 cards!"));
        return;
    }
    yard->clear();
    for(int i = 0; i < 3; i++)
        for (int j = 0; j < 6; j++){
            // qDebug()<<i<<" "<<j<<" "<<chosenName[i][j];
            if (chosenName[i][j]){
                // qDebug()<<allName[i][j];
                yard->addCard(allName[i][j],
                              cost[i][j],
                              time[i][j]);
            }
        }
    accept();
}

void CardDialog::cancelClicked()
{
    reject();
}

void CardDialog::prepareCard(int pp)
{
    int row = pp / 6;
    int col = pp % 6;
    // qDebug()<<"row is "<<row<<", and col is "<<col;
    chosenName[row][col] = ! chosenName[row][col];
    if (chosenName[row][col])
        counter++;
    else
        counter--;
    // qDebug()<<chosenName[row][col];
    // qDebug()<<allName[row][col];
}


