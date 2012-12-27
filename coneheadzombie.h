#ifndef CONEHEADZOMBIE_H
#define CONEHEADZOMBIE_H
#include "zombie.h"

class ConeheadZombie : public Zombie
{
    Q_OBJECT
public:
    explicit ConeheadZombie(Field* ff, QObject *parent = 0);
    QRectF boundingRect() const;
    QPainterPath shape() const;

signals:
    
public slots:
    
};

#endif // CONEHEADZOMBIE_H
