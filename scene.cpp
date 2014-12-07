#include <QtCore/QDebug>
#include "Constants.h"
#include "scene.h"


Scene::Scene(QObject *parent) :
    QGraphicsScene(parent)
{
    setSceneRect(0,0, (COL_NUMBER+1)*GRID_X,ROW_NUMBER*GRID_Y);

    // draw background
    setBackgroundBrush(QBrush(QColor(0,200,0)));
    for(int i= 0; i<=ROW_NUMBER; i++){
        addLine(0,i*GRID_Y,COL_NUMBER*GRID_X,i*GRID_Y);
    }
    for(int i= 0; i<ROW_NUMBER; i++)
        addMower(i);
    for(int i= 0; i<=COL_NUMBER; i++){
        addLine(i*GRID_X,0,i*GRID_X,ROW_NUMBER*GRID_Y);
    }
    prepare = false;
    prepare4Cob = false;
    paused = false;
}

void Scene::restart()
{
    // qDebug()<<"come to Scene::restart";
    prepare = false;
    prepare4Cob = false;
    QList<QGraphicsItem*> deleteList = items();
    QGraphicsItem* temp;
    QGraphicsLineItem* line;
    QGraphicsObject* obj;
    while(!deleteList.empty()){
        temp = deleteList.takeFirst();
        // qDebug()<<"Scene::restart, trying to remove all objectives";
        line = qgraphicsitem_cast<QGraphicsLineItem*>(temp);
        removeItem(temp);
        if (!line){
            // qDebug()<<"success in casting";
            // qDebug()<<(long)obj;
            obj = qgraphicsitem_cast<QGraphicsObject*>(temp);
            obj->deleteLater();
            // qDebug()<<QString(obj->metaObject()->className());
        }
        else
            delete(temp);
        // temp->deleteLater();
    }
    pp = NULL;
    newPlant = NULL;
    target = NULL;
    for(int i= 0; i<=ROW_NUMBER; i++){
        addLine(0,i*GRID_Y,COL_NUMBER*GRID_X,i*GRID_Y);
    }
    for(int i=0; i<ROW_NUMBER; i++)
        addMower(i);
    for(int i= 0; i<=COL_NUMBER; i++){
        addLine(i*GRID_X,0,i*GRID_X,ROW_NUMBER*GRID_Y);
    }
    paused = false;
    // qDebug()<<"finishing Scene::restart()";
}

void Scene::pause()
{
    emit pauseAll();
    paused = true;
}

void Scene::restore()
{
    emit restoreAll();
    paused = false;
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (paused)
        return;
    // qDebug()<<event->isAccepted();
    // qDebug()<<"come to Scene::mousePressEvent";
    if (prepare4Cob){
        // qDebug()<<"come to not ignore";
        if (event->buttons()==Qt::LeftButton){
            if (prepare4Cob){
                QPointF p = event->scenePos();
                // qDebug()<<p;
                QPoint point(plantPos(p));
                // qDebug()<<"prepare to sendCob";
                // qDebug()<<"at point "<<point;
                sendCob(point);
                emit sentCob();
                prepare4Cob = false;
                target->deleteLater();
                event->accept();
            }
        }
        else{
            prepare4Cob = false;
            target->deleteLater();
            event->ignore();
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (paused)
        return;
    QGraphicsScene::mouseMoveEvent(event);
    // qDebug()<<"come to Scene::mouseMoveEvent";
    // qDebug()<<"prepare is "<<prepare<<", and prepare4Cob is "<<prepare4Cob;
    if (prepare){
        newPlant->setPos(plantPos(event->scenePos()));
        update();
    }
    if (prepare4Cob){
        // qDebug()<<"come to prepare4Cob";
        target->setPos(targetPos(event->scenePos()));
        update();
    }
}

void Scene::setNewPlant(Plant* p)
{
    prepare = true;
    newPlant = p;
}

void Scene::alreadyPlanted()
{
    prepare = false;
    newPlant = NULL;
}

const QPoint Scene::plantPos(const QPointF &p) const
{
    QPoint point((int)((p.x())/GRID_X),(int)((p.y())/GRID_Y));
    if (point.x()<0)
        point.setX(0);
    if (point.x()>=COL_NUMBER)
        point.setX(COL_NUMBER-1);
    if (point.y()<0)
        point.setY(0);
    if (point.y()>=ROW_NUMBER)
        point.setY(ROW_NUMBER-1);
    point.setX(point.x()*GRID_X);
    point.setY(point.y()*GRID_Y);
    return point;
}

const QPoint Scene::targetPos(const QPointF &p) const
{
    QPoint point(plantPos(p));
    return QPoint(point.x()+GRID_X/2,point.y()+GRID_Y/2);
}

void Scene::prepareForCob(Plant* p)
{
    // qDebug()<<"come to Scene::prepareForCob";
    pp = p;
    target = new Target;
    target->setPos(-200,-200);
    addItem(target);
    prepare4Cob=true;
    // qDebug()<<prepare4Cob;
}

void Scene::sendCob(QPoint &p)
{
    Cob* cob = new Cob(p);
    connect(cob,SIGNAL(explode(Cob*)),this,SLOT(receiveCob(Cob*)));
    connect(this,SIGNAL(pauseAll()),cob,SLOT(pause()));
    connect(this,SIGNAL(restoreAll()),cob,SLOT(restore()));
    cob->setPos(pp->pos());
    addItem(cob);
}

void Scene::receiveCob(Cob* cob)
{
    QGraphicsPixmapItem *pic = addPixmap(QPixmap(":/images/cobImpact.png"));
    QPoint p= cob->getTarget();
    pic->setPos(p.x()-20,p.y()-20);
    list.append(pic);
    // NOTE, here is a non-pausable code !
    QTimer::singleShot(1000,this,SLOT(clearImpact()));
    emit explodeAt((p.y())/GRID_Y,p.x()/GRID_X);
    // qDebug()<<"Scene::receiveCob trying to remove cob";
    removeItem(cob);
    cob->deleteLater();
}

void Scene::clearImpact()
{
    if (list.isEmpty()){
        qDebug()<<"list empty!! in Scene::clearImpact";
        // should never be visited
    }
    else{
        // qDebug()<<"Scene::clearImpact, trying to remove Impacts";
        removeItem(list.first());
        list.removeFirst();
    }
}

void Scene::addMower(int row)
{
    Mower* mower = new Mower(row);
    connect(mower,SIGNAL(clearLine(int)),this,SIGNAL(clearLine(int)));
    connect(mower,SIGNAL(sendHit(Zombie*,int,int)),this,SIGNAL(sendHit(Zombie*,int,int)));
    connect(mower,SIGNAL(destroyMe(Mower*)),this,SLOT(destroyMower(Mower*)));
    mower->setPos(0-GRID_X,row*GRID_Y);
    addItem(mower);
}

void Scene::destroyMower(Mower* m)
{
    removeItem(m);
}
