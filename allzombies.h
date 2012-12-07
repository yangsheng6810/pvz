#ifndef ALLZOMBIES_H
#define ALLZOMBIES_H

#include <QWidget>
#include <QLinkedList>
#include <QTimer>
#include "zombie.h"
#include "Constants.h"

class AllZombies : public QWidget
{
    Q_OBJECT
public:
    explicit AllZombies(QWidget *parent = 0);
    void addZombie(int row,int type=0);// called by AI
    bool zombieAt(int row, int col) const;

signals:
    // void zombieAt(int row, int col);
    void addZombieAt(Zombie*, int, int);
    void deleteZombie(Zombie*);
    void receiveHit(Zombie* z,int strength,int property);

public slots:
    //void deleteZombie(Zombie* deadZombie);
    // void startSendZombies();
    void sendZombies();
    void clearRow(int row);
private slots:
    void countZombies();
    void killDead(Zombie*);
private:
    QLinkedList<Zombie*> zombieList[ROW_NUMBER];
    static int originHealthPoint;
    QTimer *timer;
    int counter;
};

#endif // ALLZOMBIES_H
