#ifndef SNOWPEA_H
#define SNOWPEA_H
#include <QDebug>
#include "plant.h"

class SnowPea : public Plant
{
    Q_OBJECT
public:
    explicit SnowPea(QObject *parent = 0);

public slots:
    virtual void seeZombie(int row, int col);
    virtual void sendPea();
protected:
    int strength;
    int property;
    int counter;
};

#endif // SNOWPEA_H
