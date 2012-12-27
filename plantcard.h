#ifndef PLANTCARD_H
#define PLANTCARD_H

#include <QtGui>
#include "sunlight.h"
#include "timer.h"

class Plant;


class PlantCard : public QWidget
{
    Q_OBJECT
public:
    explicit PlantCard(QString plantName, int sun, int time, SunLight *parent);
    ~PlantCard();
    const QString name;
    QPushButton* button;
    Timer* timer;
    QProgressBar* bar;
    int getSunNeeded();

signals:
    void tryPlanting(Plant* plant, PlantCard* card);
public slots:
    void restart();
    void pause();
    void restore();
    void destroyMe();
    void recharge(void);
    void sunUpdate(int num);
    void charging(void);
protected:
    int waiting;
    int sunNeeded;
    QPixmap* pixmap;
    QVBoxLayout* layout;
    bool paused;
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
