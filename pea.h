#ifndef PEA_H
#define PEA_H

#include <QGraphicsItem>

class Zombie;

class Pea : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Pea(int Strength, int Property, QString name="pea");
    enum {Type = UserType +3};
    int type() const;
    const QString peaName;
    const QString typeName;
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    
signals:
    void sendHit(Zombie* zz, int num, int property1);
    void destroyMe(Pea *);
    
public slots:

protected:
    void advance(int step);
    int property;// 0=normal, 1=normal, 2=fire, 3=freeze, 4=butter
    int strength;
    int whichStep;
    QList<QGraphicsItem *> list;
};

#endif // PEA_H
