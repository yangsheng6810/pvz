#ifndef PLANTYARD_H
#define PLANTYARD_H

#include <QWidget>
#include "Constants.h"
#include "plantcard.h"

class PlantYard : public QWidget
{
    Q_OBJECT
public:
    explicit PlantYard(QWidget *parent = 0);
    PlantCard* allPlants[PLANT_NUMBER];
    
signals:
    
public slots:
    
};

#endif // PLANTYARD_H
