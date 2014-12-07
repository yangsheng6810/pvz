#include "field.h"
#include <QDebug>

Field::Field(SunLight* sunLight, AllZombies* zzz, QWidget *parent) :
    QWidget(parent), sun(sunLight),allZombies(zzz), prepare(false)
{
    for(int i=0; i < ROW_NUMBER; i++)
        for(int j = 0; j < COL_NUMBER; j++)
            plantField[i][j]=NULL;
    timer = new Timer();
    connect(timer,SIGNAL(timeout()),this,SLOT(scanZombies()));
    //timer->start(500);
    timer->start(0.1);

}

void Field::restart()
{
    for(int i= 0; i<ROW_NUMBER; i++)
        for(int j=0; j<COL_NUMBER; j++)
            plantField[i][j]=NULL;
            /*
            if (plantField[i][j]){
                // plantField[i][j]->deleteLater();
                plantField[i][j]=NULL;
            }
            */
    newPlant = NULL;
    prepare = false;
    timer->start();
    // qDebug()<<"finishing Field::restart()";
}

void Field::pause()
{
    emit pausePlants();
    timer->pause();
}

void Field::restore()
{
    emit restorePlants();
    timer->restore();
}

void Field::addPlant(Plant* plant, int row, int col)
{
    if (plant != 0) {
        if (row >= ROW_NUMBER || col >= COL_NUMBER){
            qDebug() << QString("Exceeds!")<<ROW_NUMBER<<" "<<row<<" "<<COL_NUMBER<<" "<<col;
            delete(plant);
            return;
        }
        // qDebug()<<QString(plant->metaObject()->className());
        if (plantField[row][col]!=NULL
                && QString(plant->metaObject()->className()) != "CobCannon"
                && QString(plant->metaObject()->className()) != "GatlingPea"){
            delete(plant);
            return;
        }
        else{
            // qDebug()<<"come to Field::addPlant";
            if (QString(plant->metaObject()->className())=="CobCannon"){
                if (plantField[row][col] == NULL){
                    // qDebug()<<"come to first if";
                    delete(plant);
                    return;
                }
                QString s1(plantField[row][col]->metaObject()->className());
                if (col >= COL_NUMBER-1 || plantField[row][col+1] == NULL){
                    // qDebug()<<"come to second if";
                    delete(plant);
                    return;
                }
                QString s2(plantField[row][col+1]->metaObject()->className());
                if (!(s1=="KernelPult" && s2=="KernelPult")){
                    // qDebug()<<s1<<" "<<s2;
                    // qDebug()<<"come to third if";
                    delete(plant);
                    return;
                }
                plantField[row][col]->deleteLater();
                plantField[row][col+1]->deleteLater();
                emit removePlantPic(plantField[row][col]);
                emit removePlantPic(plantField[row][col+1]);
                plantField[row][col+1]=plant;
            }
            else if (QString(plant->metaObject()->className())=="GatlingPea"){
                if (plantField[row][col] == NULL
                        || QString(plantField[row][col]->metaObject()->className()) != "Repeater"){
                    delete(plant);
                    return;
                }
                else{
                    plantField[row][col]->deleteLater();
                    emit removePlantPic(plantField[row][col]);
                }
            }
            plantField[row][col] = plant;
            emit addPlantPic(plant, row, col);
            connect(this,SIGNAL(zombieAt(int,int)),plant,SLOT(seeZombie(int,int)));
            connect(this,SIGNAL(sendPea()),plant,SLOT(sendPea()));
            connect(this,SIGNAL(pausePlants()),plant,SLOT(pause()));
            connect(this,SIGNAL(restorePlants()),plant,SLOT(restore()));
            // connect(plant,SIGNAL(destroyMe(Plant*)),this,SLOT(deletePlant(Plant*)));
            plant->setLocation(row,col);
            emit subSun(newCard->getSunNeeded());
            newCard->recharge();
            /*
            if (plant->plantName == "sunflower")
                connect(plant,SIGNAL(produceSunLight(int)),sun,SLOT(addSunLight(int)));
                */
            if (plant->plantName == "jalapeno")
                connect(plant,SIGNAL(clearRow(int)),allZombies,SLOT(clearRow(int)));
            if (plant->plantName == "cherryBomb")
                connect(plant,SIGNAL(clearBox(int,int)),allZombies,SLOT(clearBox(int,int)));
            if (plant->plantName == "spikeweed")
                connect(plant,SIGNAL(sendHitBox(int,int,int)),allZombies,SLOT(sendHitBox(int,int,int)));
            if (plant->plantName == "potatoMine")
                connect(plant,SIGNAL(sendHitBox(int,int,int)),allZombies,SLOT(sendHitBox(int,int,int)));
            if (plant->plantName == "squash")
                connect(plant,SIGNAL(sendHitBox(int,int,int)),allZombies,SLOT(sendHitBox(int,int,int)));
        }
    }
}

void Field::removePlant(int row, int col)
{
    if (plantField[row][col] != 0) {
        emit removePlantPic(plantField[row][col]);
        Plant* plant = plantField[row][col];
        if (QString(plant->metaObject()->className())=="CobCannon"){
            plantField[plant->myRow][plant->myCol] = NULL;
            plantField[plant->myRow][plant->myCol+1] = NULL;
        }
        else
            delete(plantField[row][col]);
        plantField[row][col] = NULL;
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
    if (QString(plantField[p->myRow][p->myCol]->metaObject()->className())=="CobCannon")
        plantField[p->myRow][p->myCol+1] = NULL;
    plantField[p->myRow][p->myCol] = NULL;
}

Plant* Field::getPlant(int row, int col)
{
    if (row >=0 && row <ROW_NUMBER && col>=0 && col<COL_NUMBER)
        return plantField[row][col];
    return NULL;
}
