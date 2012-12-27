#ifndef SPIKEWEED_H
#define SPIKEWEED_H
#include <QDebug>
#include "plant.h"

class Spikeweed : public Plant
{
    Q_OBJECT
public:
    explicit Spikeweed(QObject *parent = 0);
    QRectF boundingRect() const;
    
signals:
    void sendHitBox(int row, int col, int strength);
    
public slots:
    virtual void seeZombie(int row, int col);
    virtual void sendPea();

protected:
    int strength;
    int counter;
};

#endif // SPIKEWEED_H
