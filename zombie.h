#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QWidget>
#include <QMovie>
#include <QGraphicsObject>
#include "plant.h"
#include "field.h"
#include "timer.h"
class Field;


class Zombie : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Zombie(Field* ff, QString name="zombie", QObject* parent = 0);
    ~Zombie();
    const QString zombieName;
    const QString typeName;
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void eat(int eatNumber);
    enum { Type = UserType+1};
    int type() const;
protected:
    void advance(int step);
    QMovie* movie;
    QList<QGraphicsItem *> list;
    bool eating;
    Plant* plant;
    Field* f;
    Timer* timer;

signals:
    void stepForward();
    void hpChanged(int hp);
    void die(Zombie* zombie);
    void sendEat(Plant* p, int num);
    void youLose();
public slots:
    virtual void pause();
    virtual void restore();
    void freeze();// to be implemented
    void hitten(Zombie* z, int hitNumber, int property=0);
    // void loseMetal(); this may be implemeted in individual zombies
    // void burnt(); // reserved for explosion
private slots:
    void unfreeze();
    void tryEating();
protected:
    int healthPoint;
    int isFrozen;
    int whichStep;
    const QPoint targetPoint(const QPointF& position) const;
    bool dead;
    int xShift, yShift;
};
// note, this is only a simple implement of zombie

#endif // ZOMBIE_H
