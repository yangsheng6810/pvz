#ifndef GATLINGPEA_H
#define GATLINGPEA_H
#include "plant.h"

class GatlingPea : public Plant
{
    Q_OBJECT
public:
    explicit GatlingPea(QObject *parent = 0);
    
signals:
    
public slots:
    void seeZombie(int row, int col);
    void sendPea();
protected:
    int strength;
    int property;
    int counter;
    
};

#endif // GATLINGPEA_H
