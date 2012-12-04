#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QWidget>
#include <QGraphicsItem>

class Zombie : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Zombie(QObject *parent = 0, QString name="zombie");
    const QString zombieName;
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void hitten(int hitNumber);
    void eat(int eatNumber);
protected:
    void advance(int step);

signals:
    void stepForward();
    void hpChanged(int hp);
    void die(Zombie* zombie);
public slots:
    void freeze(int time);// to be implemented
    // void loseMetal(); this may be implemeted in individual zombies
    // void burnt(); // reserved for explosion
private slots:
    void unfreeze();
private:
    int healthPoint;
    int isFrozen;
    int whichStep;
};
// note, this is only a simple implement of zombie

#endif // ZOMBIE_H
