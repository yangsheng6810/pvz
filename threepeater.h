#ifndef THREEPEATER_H
#define THREEPEATER_H
#include "plant.h"

class Threepeater : public Plant
{
    Q_OBJECT
public:
    explicit Threepeater(QObject *parent = 0);
    QRectF boundingRect() const;
    
signals:
    
public slots:
    virtual void seeZombie(int row, int col);
    virtual void sendPea();
protected:
    int strength;
    int property;
    int counter;

};

#endif // THREEPEATER_H
