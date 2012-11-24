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

signals:
    
public slots:
    void addSunLight(int num);
    void addSunLight(void);// for debug
protected:
    int sunLight;
    QLCDNumber* lcd;
signals:
    void updateSun(int);
};

#endif // SUNLIGHT_H
