#ifndef TORCHWOOD_H
#define TORCHWOOD_H
#include "plant.h"

class Torchwood : public Plant
{
    Q_OBJECT
public:
    explicit Torchwood(QObject *parent = 0);
    
signals:
    
public slots:
protected:
    void advance(int step);
    
};

#endif // TORCHWOOD_H
