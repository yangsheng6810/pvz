#ifndef PLANT_H
#define PLANT_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMovie>

class Plant : public QWidget
{
    Q_OBJECT
public:
    explicit Plant(QWidget *parent = 0);

signals:

public slots:
    void bitten(int num);

protected:
    int healthPoint;
    void die();

};

#endif // PLANT_H
