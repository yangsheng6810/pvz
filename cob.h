#ifndef COB_H
#define COB_H

#include <QGraphicsObject>
#include <QPainter>
#include "timer.h"

class Cob : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Cob(QPoint &p);
    ~Cob();
    enum {Type = UserType +10};
    int type() const;
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QPoint getTarget();
signals:
    void explode(Cob* cc);
public slots:
    void pause();
    void restore();
    void reverse();

protected:
    void advance(int step);
    bool up;
    QTransform transform;
    QPoint target;
    Timer* timer;
};

#endif // COB_H
