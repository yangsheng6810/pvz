#ifndef GARDEN_H
#define GARDEN_H

#include <QtGui/QtGui>
#include "plant.h"
#include "zombie.h"
#include "sunlight.h"
#include "scene.h"
#include "timer.h"
class Pea;
class Sun;

QT_BEGIN_NAMESPACE
class QMouseEvent;
QT_END_NAMESPACE

class Garden : public QWidget
{
    Q_OBJECT
public:
    explicit Garden(SunLight *sun, QWidget *parent = 0);
    Scene* scene;
    // QGraphicsScene* scene;
    QGraphicsView* view;
signals:
    void addPlantAt(Plant* plant, int row, int col);
    void removePlantAt(int row, int col);
    void sendHit(Zombie* z, int strength, int property);
    void sendEatTo(Plant* pp, int num);
    void destroyPlant(Plant* plant);
    void emitSun(int);
    void explodeAt(int row, int col);
    void restartScene();
    void pauseScene();
    void restoreScene();
    void clearLine(int row);
public slots:
    void restart();
    void pause();
    void restore();
    void addPlant(Plant* plant, int row, int col);
    void removePlant(Plant* plant);
    void prepareToPlant(Plant* plant);
    void prepareToRemove(void);
    void addZombieAt(Zombie* zombie, int row, int col);
    void addPea(int row, int col, int strength, int property, int targetCol=1000);
    void deleteZombie(Zombie* z);
    void destroyPea(Pea* p);
    void deletePlant(Plant* p);
    void produceSun(Plant* p);
    void destroySun(Sun* s);
    void emitCob();
    /*
    void collectSun(Plant* p);// to be changed
    */

protected:
    virtual void mousePressEvent(QMouseEvent *event);

    Plant* newPlant;
    bool prepare;
    bool prepare2Remove;
    bool prepare4Cob;
    SunLight* sun;
    const QPoint targetPoint(const QPointF &position) const;
    const QPoint scenePos(const QPointF &position) const;
    const QPointF actualPos(int row, int col) const;
    const QPoint plantPos(const QPointF &position) const;
    Timer* timer;
    bool paused;
};

#endif // GARDEN_H
