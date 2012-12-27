#ifndef PLANTYARD_H
#define PLANTYARD_H

#include <QWidget>
#include <QHBoxLayout>
#include "Constants.h"
#include "plantcard.h"
#include "plant.h"
#include "field.h"
#include "sunlight.h"

class PlantYard : public QWidget
{
    Q_OBJECT
public:
    explicit PlantYard(SunLight* mySun, Field* myField,QWidget *parent = 0);
    PlantCard* allPlants[PLANT_NUMBER];
    
signals:
    void restartAllCards();
    void pauseAllCards();
    void restoreAllCards();
    void destroyAllCards();
    
public slots:
    void addCard(QString name, int cost, int time);
    void restart();
    void pause();
    void restore();
    void clear();

protected:
    Field* f;
    SunLight* sun;
    QHBoxLayout* layout;

};

#endif // PLANTYARD_H
