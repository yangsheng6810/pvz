#ifndef ALLZOMBIES_H
#define ALLZOMBIES_H

#include <QWidget>
#include <QLinkedList>
#include <QTimer>
#include "zombie.h"

struct zombiePack
{
    Zombie* zombie;
    int row;
    int col;
};

class AllZombies : public QWidget
{
    Q_OBJECT
public:
    explicit AllZombies(QWidget *parent = 0);
    void addZombie(int row,int type=0);// called by others

signals:
    void zombieAt(int row, int col);
    
public slots:
    void peaShoot(int row, int colFrom, int strength=1);
    void reversePeaShoot(int row, int colFrom, int strength =1);
    //void deleteZombie(Zombie* deadZombie);
private slots:
    void sendMessage();
private:
    QLinkedList<zombiePack> zombieList;
    static int originHealthPoint;
    QTimer *timer;
};

#endif // ALLZOMBIES_H
