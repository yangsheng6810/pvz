#include "field.h"
#include <QRect>
#include <QPoint>
#include <QDebug>

Field::Field(SunLight* sunLight,QWidget *parent) :
    QWidget(parent), prepare(false), sun(sunLight)
{
    for(int i=0; i < ROW_NUMBER; i++)
        for(int j = 0; j < COL_NUMBER; j++)
            plantField[i][j]=NULL;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(scanZombies()));
    timer->start(10*1000);

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
            if (plant->plantName=="peashooter"){
                emit subSun(100);
                newCard->recharge();
            }
            else if (plant->plantName == "sunflower"){
                connect(plant,SIGNAL(produceSunLight(int)),sun,SLOT(addSunLight(int)));
                emit subSun(50);
                newCard->recharge();
            }
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

}
