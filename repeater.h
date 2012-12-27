#ifndef REPEATER_H
#define REPEATER_H
#include "plant.h"

class Repeater : public Plant
{
    Q_OBJECT
public:
    explicit Repeater(QObject *parent = 0);
    
signals:
    
public slots:
    void seeZombie(int row, int col);
    void sendPea();
protected:
    int strength;
    int property;
    int counter;
    
};

#endif // REPEATER_H
