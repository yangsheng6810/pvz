#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include "plant.h"
#include "target.h"
#include "cob.h"
#include "mower.h"

QT_BEGIN_NAMESPACE
class QMouseEvent;
QT_END_NAMESPACE

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = 0);
    
signals:
    void explodeAt(int row, int col);
    void pauseAll();
    void restoreAll();
    void sentCob();
    void clearLine(int row);
    void sendHit(Zombie*, int,int);
    
public slots:
    void restart();
    void pause();
    void restore();
    void sendCob(QPoint &point);
    void setNewPlant(Plant* p);
    void alreadyPlanted();
    void prepareForCob(Plant *p);
    void receiveCob(Cob *cob);
    void addMower(int row);
    void destroyMower(Mower* m);

private slots:
    void clearImpact();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    bool prepare;
    bool prepare4Cob;
    Plant* newPlant;
    Target* target;
    const QPoint plantPos(const QPointF &p) const;
    const QPoint targetPos(const QPointF &p) const;
    Plant* pp;
    QList<QGraphicsPixmapItem*> list;
    bool paused;
    
};

#endif // SCENE_H
