#ifndef SUN_H
#define SUN_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

QT_BEGIN_NAMESPACE
class QMouseEvent;
QT_END_NAMESPACE

class Sun : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Sun(int sun, QObject *parent = 0);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    int sunLight;
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    
signals:
    void emitSun(int num);
    void destroyMe(Sun* sun);
    
public slots:
    
};

#endif // SUN_H
