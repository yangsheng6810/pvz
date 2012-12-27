#ifndef MINEPOTATO_H
#define MINEPOTATO_H
#include "plant.h"
#include "timer.h"

class PotatoMine : public Plant
{
    Q_OBJECT
public:
    explicit PotatoMine(QObject *parent = 0);
    ~PotatoMine();
    virtual void setPlanted();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    
signals:
    void sendHitBox(int row, int col, int strength);
    
public slots:
    void explode();
    void pause();
    void restore();
    void ready();
    void seeZombie(int row, int col);
    void sendPea();

protected:
    Timer* timer;
    bool prepare;
    int counter;
};

#endif // MINEPOTATO_H
