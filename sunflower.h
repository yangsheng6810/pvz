#ifndef SUNFLOWER_H
#define SUNFLOWER_H
#include "plant.h"


class SunFlower : public Plant
{
    Q_OBJECT
public:
    explicit SunFlower(QObject *parent = 0);
    ~SunFlower();
signals:
    void produceSunLight(int num);
    void produceSun(Plant* plant);
public slots:
    void sunLight();
    void pause();
    void restore();
protected:
    Timer* timer;
};

// may be it is a good idea to put all different plants in a single file?
// may be not?
#endif // SUNFLOWER_H
