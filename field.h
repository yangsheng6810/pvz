#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include "Constants.h"
#include "allzombies.h"
#include "plant.h"
#include "plantcard.h"
#include "sunlight.h"
#include "timer.h"
class AllZombies;
class Zombie;

class Field : public QWidget
{
    Q_OBJECT
public:
    explicit Field(SunLight* sunLight, AllZombies* zzz, QWidget *parent = 0);
    SunLight* sun;

private:
    Plant* plantField[ROW_NUMBER][COL_NUMBER];
    //QWidget* plantField[ROW_NUMBER][COL_NUMBER];
    AllZombies* allZombies;
signals:
    void pausePlants();
    void restorePlants();
    void sendPea();// type is used for potential useage
    void zombieAt(int row, int col);
    // maybe sendWatermelon
    void plantSucceed(QString plantName);
    void addPlantPic(Plant* plant, int row, int col);
    void removePlantPic(Plant* plant);
    void prepareToPlant(Plant* plant);
    void subSun(int);
public slots:
    void restart();
    void pause();
    void restore();
    void addPlant(Plant *plant, int row, int col);
    void removePlant(int row, int col);
    void removePlantDebug(void);
    void addPlant(Plant *plant, PlantCard* card);
    void scanZombies(void);
    void deletePlant(Plant*);
    Plant* getPlant(int row, int col);
protected:
    Plant* newPlant;
    PlantCard* newCard;
    bool prepare;
    Timer* timer;

};

#endif // FIELD_H
