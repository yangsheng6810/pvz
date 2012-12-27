#ifndef BUCKETHEADZOMBIE_H
#define BUCKETHEADZOMBIE_H
#include "zombie.h"

class BucketheadZombie : public Zombie
{
    Q_OBJECT
public:
    explicit BucketheadZombie(Field* ff,QObject *parent = 0);
    QRectF boundingRect() const;
    QPainterPath shape() const;

signals:
    
public slots:
    
};

#endif // BUCKETHEADZOMBIE_H
