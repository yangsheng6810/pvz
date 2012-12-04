#ifndef SUNFLOWER_H
#define SUNFLOWER_H
#include "plant.h"


class SunFlower : public Plant
{
    Q_OBJECT
public:
    explicit SunFlower(QObject *parent = 0);
signals:
    void produceSunLight(int num);
public slots:
    void sunLight();
};

// may be it is a good idea to put all different plants in a single file?
// may be not?
#endif // SUNFLOWER_H
