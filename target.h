#ifndef TARGET_H
#define TARGET_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Target : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Target(QObject *parent = 0);
    enum {Type = UserType +50};
    int type() const;
    
signals:
    
public slots:

protected:
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

};

#endif // TARGET_H
