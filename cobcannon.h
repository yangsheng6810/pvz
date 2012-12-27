#ifndef COBCANNON_H
#define COBCANNON_H
#include "plant.h"
#include <QGraphicsSceneMouseEvent>
#include "timer.h"

class CobCannon : public Plant
{
    Q_OBJECT
public:
    explicit CobCannon(QObject *parent = 0);
    ~CobCannon();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    
signals:
    void prepareToShoot(Plant* p);
    
public slots:
    void pause();
    void restore();

private slots:
    void recharge();
    void shoot();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    bool prepare;
    Timer* timer;
    
};

#endif // COBCANNON_H
