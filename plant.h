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
#include <QGraphicsItem>
//#include <QMetaType>

class Plant : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Plant(QObject *parent = 0, QString name="peashooter");
    const QString plantName;
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

signals:
    void hpChanged(int hp);
public slots:
    void bitten();
    void resetHealthPoint();

protected:
    int healthPoint;
    void die();
    static int originHealthPoint;
    void advance(int step);

};

#endif // PLANT_H
