#ifndef SUNLIGHT_H
#define SUNLIGHT_H

#include <QtGui/QWidget>
#include <QtGui/QLCDNumber>
#include <QtGui/QVBoxLayout>
#include <QtGui/QPushButton>

class SunLight : public QWidget
{
    Q_OBJECT
public:
    explicit SunLight(QWidget *parent = 0);
    bool sufficientSunLight(int num);

public slots:
    void restart();
    void pause();
    void restore();
    void addSunLight(int num);
    void addSunLight(void);// for debug
    void subtractSunLight(int num);// caller responsible for sufficient sunlight
protected:
    int sunLight;
    QLCDNumber* lcd;
    bool paused;
signals:
    void updateSun(int);
    //void insufficientSunLight();
};

#endif // SUNLIGHT_H
