#ifndef KERNELPULF_H
#define KERNELPULF_H
#include "plant.h"

class KernelPult : public Plant
{
    Q_OBJECT
public:
    explicit KernelPult(QObject *parent = 0);
    QRectF boundingRect() const;
    
signals:
    
public slots:
    virtual void seeZombie(int row, int col);
    virtual void sendPea();
protected:
    int strength;
    int property;
    int counter;
    int tempCol;

};

#endif // KERNELPULF_H
