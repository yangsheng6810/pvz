#include "tallnut.h"

TallNut::TallNut(QObject *parent) :
    Plant("tallNut")
{
    healthPoint = 4000;
    xShift = 0;
    yShift = -20;
}
