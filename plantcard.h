#ifndef PLANTCARD_H
#define PLANTCARD_H

#include <QWidget>

class PlantCard : public QWidget
{
    Q_OBJECT
public:
    explicit PlantCard(QWidget *parent, int recharge, int sun);

signals:
    
public slots:
    void recharge(void);
private:
    int rechargeTime;
    int sunCost;
};

#endif // PLANTCARD_H
