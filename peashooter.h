#ifndef PEASHOOTER_H
#define PEASHOOTER_H
#include "plant.h"
#include <QDebug>

class PeaShooter : public Plant
{
    Q_OBJECT
public:
    explicit PeaShooter(QObject *parent = 0);
    
signals:
    // void emitPea(int row, int col, int strength, int property);// 0=normal, 1=fire, 2=freeze, 3=butter
    
public slots:
    virtual void seeZombie(int row, int col);
    virtual void sendPea();
protected:
    int strength;
    int property;
    int counter;
};

#endif // PEASHOOTER_H
