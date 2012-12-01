#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QWidget>

class Zombie : public QWidget
{
    Q_OBJECT
public:
    explicit Zombie(QWidget *parent = 0, QString name="zombie");
    const QString zombieName;
    void hitten(int hitNumber);
    void eat(int eatNumber);
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
};
// note, this is only a simple implement of zombie

#endif // ZOMBIE_H
