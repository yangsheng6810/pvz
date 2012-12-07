#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QWidget>
#include <QMovie>
#include <QGraphicsItem>
#include "plant.h"


class Zombie : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Zombie(QObject *parent = 0, QString name="zombie");
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

signals:
    void stepForward();
    void hpChanged(int hp);
    void die(Zombie* zombie);
    void sendEat(Plant* p, int num);
public slots:
    void freeze();// to be implemented
    void hitten(Zombie* z, int hitNumber, int property=0);
    // void loseMetal(); this may be implemeted in individual zombies
    // void burnt(); // reserved for explosion
private slots:
    void unfreeze();
    void tryEating();
private:
    int healthPoint;
    int isFrozen;
    int whichStep;
};
// note, this is only a simple implement of zombie

#endif // ZOMBIE_H
