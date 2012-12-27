#ifndef ALLZOMBIES_H
#define ALLZOMBIES_H

#include <QWidget>
#include <QLinkedList>
#include <QTimer>
#include "field.h"
#include "zombie.h"
#include "Constants.h"
#include "timer.h"
class Field;
class Zombie;

class AllZombies : public QWidget
{
    Q_OBJECT
public:
    explicit AllZombies(QWidget *parent = 0);
    void addZombie(int row,int type=0);// called by AI
    bool zombieAt(int row, int col) const;
    void setField(Field* ff);

signals:
    // void zombieAt(int row, int col);
    void addZombieAt(Zombie*, int, int);
    void deleteZombie(Zombie*);
    void receiveHit(Zombie* z,int strength,int property);
    void pauseAllZombies();
    void restoreAllZombies();
    void youLose();

public slots:
    //void deleteZombie(Zombie* deadZombie);
    // void startSendZombies();
    void restart();
    void pause();
    void restore();
    void sendZombies();
    void clearRow(int row);
    void clearBox(int row, int col);
    void sendHitBox(int row, int col, int strength);
private slots:
    void countZombies();
    void killDead(Zombie*);
private:
    QLinkedList<Zombie*> zombieList[ROW_NUMBER];
    static int originHealthPoint;
    Timer *timer;
    int counter;
    Field* f;
};

#endif // ALLZOMBIES_H
