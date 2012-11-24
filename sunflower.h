#ifndef SUNFLOWER_H
#define SUNFLOWER_H
#include "plant.h"


class SunFlower : public Plant
{
    Q_OBJECT
public:
    explicit SunFlower(QWidget *parent = 0);
signals:
    void produceSunLight(int num);
public slots:
    void sunLight();
};

#endif // SUNFLOWER_H
