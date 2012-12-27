#ifndef PEA_H
#define PEA_H

#include <QGraphicsObject>

class Zombie;

class Pea : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Pea(int Strength, int Property, int row, QString name="pea", int targetCol = 1000);
    enum {Type = UserType +3};
    int type() const;
    const QString peaName;
    const QString typeName;
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    int getProperty();
    void setProperty(int newProperty);
    
signals:
    void sendHit(Zombie* zz, int num, int property1);
    void destroyMe(Pea *);
    
public slots:

protected:
    void advance(int step);
    int property;// 0=normal, 1=normal, 2=fire, 3=freeze, 4=butter
    int strength;
    int whichStep;
    int tCol;
    int myRow;
    qreal ySpeed;
    QList<QGraphicsItem *> list;
};

#endif // PEA_H
