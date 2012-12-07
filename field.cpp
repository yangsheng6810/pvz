#include "field.h"
#include <QRect>
#include <QPoint>
#include <QDebug>

Field::Field(SunLight* sunLight, AllZombies* zzz, QWidget *parent) :
    QWidget(parent), sun(sunLight),allZombies(zzz), prepare(false)
{
    for(int i=0; i < ROW_NUMBER; i++)
        for(int j = 0; j < COL_NUMBER; j++)
            plantField[i][j]=NULL;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(scanZombies()));
    timer->start(500);

}

void Field::addPlant(Plant* plant, int row, int col)
{
    if (plant != 0) {
        if (row >= ROW_NUMBER || col >= COL_NUMBER){
            qDebug() << QString("Exceeds!")<<ROW_NUMBER<<" "<<row<<" "<<COL_NUMBER<<" "<<col;
            delete(plant);
            return;
        }
        if (plantField[row][col]!=NULL){
            delete(plant);
            return;
        }
        else{
            plantField[row][col] = plant;
            emit addPlantPic(plant, row, col);
            connect(this,SIGNAL(zombieAt(int,int)),plant,SLOT(seeZombie(int,int)));
            connect(this,SIGNAL(sendPea()),plant,SLOT(sendPea()));
            // connect(plant,SIGNAL(destroyMe(Plant*)),this,SLOT(deletePlant(Plant*)));
            plant->setLocation(row,col);
            emit subSun(newCard->getSunNeeded());
            newCard->recharge();
            if (plant->plantName == "sunflower")
                connect(plant,SIGNAL(produceSunLight(int)),sun,SLOT(addSunLight(int)));
            if (plant->plantName == "jalapeno")
                connect(plant,SIGNAL(clearRow(int)),allZombies,SLOT(clearRow(int)));
        }
    }
}

void Field::removePlant(int row, int col)
{
    if (plantField[row][col] != 0) {
        emit removePlantPic(plantField[row][col]);
        delete(plantField[row][col]);
        plantField[row][col] = 0;
    }
}

void Field::removePlantDebug()
{
    removePlant(3,0);
}

void Field::addPlant(Plant *plant, PlantCard* card)
{
    prepare = true;
    newPlant = plant;
    newCard = card;
    emit prepareToPlant(plant);
}

void Field::scanZombies()
{
    // PeaShooter* peashooter;
    // qDebug()<<"come to Field::scanZombies";
    for(int i=0; i < ROW_NUMBER; i++)
        for(int j=0; j< COL_NUMBER+1; j++)
            if(allZombies->zombieAt(i,j)){
                // qDebug()<<"sees a zombie!";
                emit zombieAt(i,j);
        }
    // the following lines are for debug
    /*
    emit zombieAt(0,5);
    emit zombieAt(1,5);
    emit zombieAt(2,2);
    */
    emit sendPea();
}

void Field::deletePlant(Plant* p)
{
    // qDebug()<<"come to Field::deletePlant";
    plantField[p->myRow][p->myCol] = NULL;
}
