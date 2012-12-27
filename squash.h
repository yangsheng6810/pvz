#ifndef SQUASH_H
#define SQUASH_H
#include "plant.h"


class Squash : public Plant
{
    Q_OBJECT
public:
    explicit Squash(QObject *parent = 0);
    
signals:
    void sendHitBox(int row, int col, int strength);
    
public slots:
    void seeZombie(int row, int col);
    // void sendPea();
protected:
    int counter;
    int ySpeed;
    void advance(int step);
    
};

#endif // SQUASH_H
