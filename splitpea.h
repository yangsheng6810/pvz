#ifndef SPLITPEA_H
#define SPLITPEA_H
#include "plant.h"

class SplitPea : public Plant
{
    Q_OBJECT
public:
    explicit SplitPea(QObject *parent = 0);
    QRectF boundingRect() const;
    
signals:
    
public slots:
    virtual void seeZombie(int row, int col);
    virtual void sendPea();
protected:
    int strength;
    int property;
    int counter;
};

#endif // SPLITPEA_H
