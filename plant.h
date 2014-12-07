#ifndef PLANT_H
#define PLANT_H

#include <QtGui/QtGui>
#include <QtGui/QGraphicsSceneMouseEvent>
#include "timer.h"

QT_BEGIN_NAMESPACE
class QMouseEvent;
QT_END_NAMESPACE

class Plant : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Plant(QString name="peashooter", QObject* parent=0);
    ~Plant();
    enum { Type = UserType + 2 };
    const QString plantName;
    const QString typeName;
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    int myRow, myCol;
    int type() const;
    virtual void setPlanted();

signals:
    void hpChanged(int hp);
    void emitPea(int row, int col, int strength, int property, int tempCol=1000);
    void destroyMe(Plant*);
    // 0=normal, 1=fire, 2=freeze, 3=butter
public slots:
    virtual void pause();
    virtual void restore();
    void bitten(Plant *pp, int num);
    // void resetHealthPoint();
    void setLocation(int row, int col);
    virtual void seeZombie(int row, int col);
    virtual void sendPea();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    int healthPoint;
    void die();
    int originHealthPoint;
    void advance(int step);
    bool hasZombie;
    int whichStep;
    QMovie* movie;
    bool planted;
    int xShift,yShift;

};

#endif // PLANT_H
