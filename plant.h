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
#include <QString>
//#include <QMetaType>

class Plant : public QWidget
{
    Q_OBJECT
public:
    explicit Plant(QWidget *parent = 0, QString name="peashooter");
    QLCDNumber *hp;
    const QString plantName;
signals:
    void hpChanged(int hp);
public slots:
    void bitten();
    void resetHealthPoint();

protected:
    int healthPoint;
    void die();
    static int originHealthPoint;
};

#endif // PLANT_H
