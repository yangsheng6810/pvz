#ifndef SUNLIGHT_H
#define SUNLIGHT_H

#include <QWidget>
#include <QLCDNumber>
#include <QHBoxLayout>
#include <QPushButton>

class SunLight : public QWidget
{
    Q_OBJECT
public:
    explicit SunLight(QWidget *parent = 0);
    bool sufficientSunLight(int num);

public slots:
    void addSunLight(int num);
    void addSunLight(void);// for debug
    void subtractSunLight(int num);// caller responsible for sufficient sunlight
protected:
    int sunLight;
    QLCDNumber* lcd;
signals:
    void updateSun(int);
    //void insufficientSunLight();
};

#endif // SUNLIGHT_H
