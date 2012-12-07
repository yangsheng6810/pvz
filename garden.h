#ifndef GARDEN_H
#define GARDEN_H

#include <QWidget>
#include "plant.h"
#include "zombie.h"
class Pea;

QT_BEGIN_NAMESPACE
class QMouseEvent;
QT_END_NAMESPACE

class Garden : public QWidget
{
    Q_OBJECT
public:
    explicit Garden(QWidget *parent = 0);
    QGraphicsScene* scene;
    QGraphicsView* view;
signals:
    void addPlantAt(Plant* plant, int row, int col);
    void removePlantAt(int row, int col);
    void sendHit(Zombie* z, int strength, int property);
    void sendEatTo(Plant* pp, int num);
    void destroyPlant(Plant* plant);
public slots:
    void addPlant(Plant* plant, int row, int col);
    void removePlant(Plant* plant);
    void prepareToPlant(Plant* plant);
    void prepareToRemove(void);
    void addZombieAt(Zombie* zombie, int row, int col);
    void addPea(int row, int col, int strength, int property);
    void deleteZombie(Zombie* z);
    void destroyPea(Pea* p);
    void deletePlant(Plant* p);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    Plant* newPlant;
    bool prepare;
    bool prepare2Remove;
    const QPoint targetPoint(const QPointF &position) const;
    const QPoint scenePos(const QPointF &position) const;
    const QPointF actualPos(int row, int col) const;
};

#endif // GARDEN_H
