#ifndef PLANTCARD_H
#define PLANTCARD_H

#include <QWidget>
#include <QPushButton>
#include <QPixmap>
#include <QPoint>
#include <QProgressBar>
#include "sunlight.h"

class Plant;


class PlantCard : public QWidget
{
    Q_OBJECT
public:
    explicit PlantCard(QString plantName, int sun, int time, SunLight *parent);
    const QString name;
    QPushButton* button;
    QTimer* timer;
    QProgressBar* bar;

signals:
    void tryPlanting(Plant* plant, PlantCard* card);
public slots:
    void recharge(void);
    void sunUpdate(int num);
    void charging(void);
protected:
    int waiting;
    int sunNeeded;
private slots:
    void buttonEnable(void);
    void buttonClicked(void);
private:
    const int rechargeTime;
    int sunCost;
    SunLight* theSun;
    bool sufficientSun;
};

#endif // PLANTCARD_H
