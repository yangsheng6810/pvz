#ifndef MELONPULT_H
#define MELONPULT_H
#include "plant.h"

class MelonPult : public Plant
{
    Q_OBJECT
public:
    explicit MelonPult(QObject *parent = 0);
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

#endif // MELONPULT_H
