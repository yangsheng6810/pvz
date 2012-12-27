#ifndef MOWER_H
#define MOWER_H

#include <QGraphicsObject>
#include <QPainter>
#include "zombie.h"

class Mower : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Mower(int row, QObject *parent = 0);
    ~Mower();
    enum {Type = UserType + 1000};
    int type() const;
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    int myRow;
    
signals:
    void clearLine(int myRow);
    void sendHit(Zombie* z, int strength, int property);
    void destroyMe(Mower* mm);
    
public slots:
protected:
    void advance(int step);
    bool running;
    // QPixmap* pic;
    
};

#endif // MOWER_H
