#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QGridLayout>
#include "Constants.h"
#include "plant.h"
#include "plantcard.h"
#include "sunlight.h"

class Field : public QWidget
{
    Q_OBJECT
public:
    explicit Field(SunLight* sunLight, QWidget *parent = 0);
    SunLight* sun;

private:
    Plant* plantField[ROW_NUMBER][COL_NUMBER];
    //QWidget* plantField[ROW_NUMBER][COL_NUMBER];
    QGridLayout* grid;// not a good idea
signals:
    void sendPea(int row, int col, int type);// type is used for potential useage
    // maybe sendWatermelon
    void plantSucceed(QString plantName);
    void addPlantPic(Plant* plant, int row, int col);
    void removePlantPic(Plant* plant);
    void prepareToPlant(Plant* plant);
    void subSun(int);
public slots:
    void addPlant(Plant *plant, int row, int col);
    void removePlant(int row, int col);
    void removePlantDebug(void);
    void addPlant(Plant *plant, PlantCard* card);
    void scanZombies(void);
protected:
    Plant* newPlant;
    PlantCard* newCard;
    bool prepare;
    QTimer* timer;

};

#endif // FIELD_H
