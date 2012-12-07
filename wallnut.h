#ifndef WALLNUT_H
#define WALLNUT_H
#include "plant.h"

class WallNut : public Plant
{
    Q_OBJECT
public:
    explicit WallNut(QObject *parent = 0);
};

#endif // WALLNUT_H
