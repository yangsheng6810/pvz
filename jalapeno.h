#ifndef JALAPENO_H
#define JALAPENO_H
#include "plant.h"

class Jalapeno : public Plant
{
    Q_OBJECT
public:
    explicit Jalapeno(QObject *parent = 0);
    ~Jalapeno();
    virtual void setPlanted();
    
signals:
    void clearRow(int row);
    
public slots:
    void pause();
    void restore();

private slots:
    void explode();

protected:
    Timer* timer;
};

#endif // JALAPENO_H
