#include "wallnut.h"

WallNut::WallNut(QObject *parent):
    Plant(parent, "wallNut")
{
    healthPoint = 2000;
}
