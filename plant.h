#ifndef PLANT_H
#define PLANT_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMovie>
#include <QtGui>
#include <QFrame>
#include <QLCDNumber>

class Plant : public QWidget
{
    Q_OBJECT
public:
    explicit Plant(QWidget *parent = 0);
    QLCDNumber *hp;
signals:
    void hpChanged(int hp);
public slots:
    void bitten();

protected:
    int healthPoint;
    void die();
};

#endif // PLANT_H
