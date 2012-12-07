#ifndef JALAPENO_H
#define JALAPENO_H
#include "plant.h"

class Jalapeno : public Plant
{
    Q_OBJECT
public:
    explicit Jalapeno(QObject *parent = 0);
    virtual void setPlanted();
    
signals:
    void clearRow(int row);
    
public slots:

private slots:
    void explode();
    
};

#endif // JALAPENO_H
