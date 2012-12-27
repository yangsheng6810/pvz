#ifndef CHERRYBOMB_H
#define CHERRYBOMB_H
#include "plant.h"
#include "timer.h"

class CherryBomb : public Plant
{
    Q_OBJECT
public:
    explicit CherryBomb(QObject *parent = 0);
    ~CherryBomb();
    virtual void setPlanted();
    
signals:
    void clearBox(int row, int col);
    
public slots:
    void explode();
    void pause();
    void restore();

protected:
    Timer* timer;
    
};

#endif // CHERRYBOMB_H
