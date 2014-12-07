#include <QtCore/QDebug>
#include "garden.h"
#include "zombie.h"
#include "plant.h"
#include "sunflower.h"
#include "Constants.h"
#include "pea.h"
#include "sun.h"
#include "scene.h"


Garden::Garden(SunLight* mySun,QWidget *parent) :
    QWidget(parent),sun(mySun)
{
    prepare = false;
    prepare2Remove = false;
    prepare4Cob = false;
    // scene = new QGraphicsScene;
    scene = new Scene;
    connect(scene,SIGNAL(explodeAt(int, int)),this,SIGNAL(explodeAt(int, int)));
    connect(this,SIGNAL(restartScene()),scene,SLOT(restart()));
    connect(this,SIGNAL(pauseScene()),scene,SLOT(pause()));
    connect(this,SIGNAL(restoreScene()),scene,SLOT(restore()));
    connect(scene,SIGNAL(clearLine(int)),this,SIGNAL(clearLine(int)));
    connect(scene,SIGNAL(sendHit(Zombie*,int,int)),this,SIGNAL(sendHit(Zombie*,int,int)));

    // scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    // view->setBackgroundBrush(QPixmap(":/images/garden.png"));

    // view->setCacheMode(QGraphicsView::CacheBackground);
    // view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    // view->fitInView(0, 0, (COL_NUMBER+1)*GRID_X,ROW_NUMBER*GRID_Y);
    view->show();
    view->setMouseTracking(true);
    // view->setFixedSize((COL_NUMBER+1)*GRID_X,ROW_NUMBER*GRID_Y);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(view);
    setLayout(layout);

    // qDebug()<<"come before timer";
    timer = new Timer();
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start((qreal)1/33);

    connect(this,SIGNAL(emitSun(int)),sun,SLOT(addSunLight(int)));
    this->setMouseTracking(true);

    paused = false;

}

void Garden::restart()
{
    // qDebug()<<"come to Garden::restart";
    newPlant = NULL;
    emit restartScene();
    paused = false;
    timer->start();
    // qDebug()<<"finishing Garden::restart";
}

void Garden::pause()
{
    emit pauseScene();
    timer->pause();
    paused = true;
}

void Garden::restore()
{
    emit restoreScene();
    timer->restore();
    paused = false;
}

void Garden::addPlant(Plant* plant, int row, int col)
{
    // qDebug()<<"come to Garden::addPlant";
    plant->setPos(actualPos(row,col));
    // scene->addItem(plant);
    connect(plant,SIGNAL(emitPea(int,int,int,int,int)), this, SLOT(addPea(int,int,int,int,int)));
    connect(this,SIGNAL(sendEatTo(Plant*,int)),plant,SLOT(bitten(Plant*, int)));
    connect(plant,SIGNAL(destroyMe(Plant*)),this,SLOT(deletePlant(Plant*)));
    if (QString(plant->metaObject()->className())=="SunFlower"){
        connect(plant,SIGNAL(produceSun(Plant*)),this,SLOT(produceSun(Plant*)));
    }
    if (QString(plant->metaObject()->className())=="CobCannon"){
        // connect(plant,SIGNAL(emitCob()),this,SLOT(emitCob()));
        connect(plant,SIGNAL(prepareToShoot(Plant*)),scene,SLOT(prepareForCob(Plant*)));
        connect(scene,SIGNAL(sentCob()),plant,SLOT(shoot()));
    }
    plant->setPlanted();
}

void Garden::removePlant(Plant* plant)
{
    // qDebug()<<"Garden::removePlant, trying to remove plant";
    scene->removeItem(plant);
}

void Garden::addZombieAt(Zombie* zombie, int row, int col)
{
    zombie->setPos(actualPos(row,col));
    scene->addItem(zombie);
    connect(zombie,SIGNAL(sendEat(Plant*,int)),this,SIGNAL(sendEatTo(Plant*,int)));
    // scene->addLine(0,0,200,200);
}

void Garden::prepareToPlant(Plant* plant)
{
    // qDebug()<<"come to Garden::prepareToPlant";
    prepare = true;
    newPlant = plant;
    plant->setPos(-200,-200);
    scene->addItem(plant);
    scene->setNewPlant(plant);
    plant->setParent(scene);
    // maybe some potential condition
}

void Garden::prepareToRemove()
{
    if (paused)
        return;
    prepare2Remove = true;
}

void Garden::mousePressEvent(QMouseEvent *event)
{
    if (paused)
        return;
    QWidget::mousePressEvent(event);
    QPoint point = targetPoint(scenePos(event->pos()));
    if (point.x()< 0 || point.x() >=COL_NUMBER || point.y() < 0 || point.y() >= ROW_NUMBER){
        event->ignore();
    }
    else {
        // QPoint point = targetPoint(event->pos());
        // qDebug()<<point;
        if (event->buttons()==Qt::LeftButton){
            if (prepare){
                emit addPlantAt(newPlant,point.y(),point.x());
                prepare = false;
                scene->alreadyPlanted();
                newPlant = NULL;
            }
            else if (prepare2Remove){
                emit removePlantAt(point.y(),point.x());
                prepare2Remove = false;
            }
            else{
                event->ignore();
            }
        }
        else {
            if (prepare){
                // qDebug()<<"Garden::mousePressEvent, trying to remove plant";
                scene->removeItem(newPlant);
                newPlant->deleteLater();
                scene->alreadyPlanted();
            }
            // if(prepare2Remove)
            event->ignore();
        }
    }
}

const QPoint Garden::targetPoint(const QPointF &position) const
{
    QPoint point((position.x())/GRID_X, (position.y())/GRID_Y);
    if (point.x()<0)
        point.setX(0);
    if (point.x()>=COL_NUMBER)
        point.setX(COL_NUMBER-1);
    if (point.y()<0)
        point.setY(0);
    if (point.y()>=ROW_NUMBER)
        point.setY(ROW_NUMBER-1);
    return point;
}

const QPoint Garden::scenePos(const QPointF &p) const
{
    QPointF p1(view->mapToScene(QPoint(p.x(),p.y())));
    return QPoint(p1.x()-10,p1.y()-10);// NOTE MYSTERIOUS CONSTANT!!!!!!
    /**************
      God Damn know what f**k is this!!!
      ************/
}

const QPoint Garden::plantPos(const QPointF &p) const
{
    return QPoint((int)((p.x())/GRID_X)*GRID_X,(int)((p.y())/GRID_Y)*GRID_Y);
}

const QPointF Garden::actualPos(int row, int col) const
{
       QPointF p1(col*GRID_X,row*GRID_Y);
       QPointF p2(p1.x(),p1.y());
       return p2;
}


void Garden::addPea(int row, int col, int strength, int property, int targetCol)
{
    /*
    qDebug()<<"come to addPea in Garden";
    qDebug()<<"row "<<row<<" col "<<col;
    qDebug()<<"strength "<<strength<<" property "<<property;
    */
    Pea* p;
    if (property==3)
        p = new Pea(strength,property,row,"snowpea");
    else if (property == 5)
        p = new Pea(strength,property,row,"kernel",targetCol);
    else if (property == 6)
        p = new Pea(strength, property,row,"melon",targetCol);
    else
        p = new Pea(strength,property,row);
    p->setPos(actualPos(row,col));
    connect(p,SIGNAL(sendHit(Zombie*,int,int)),this,SIGNAL(sendHit(Zombie*,int,int)));
    connect(p,SIGNAL(destroyMe(Pea*)),this,SLOT(destroyPea(Pea*)));
    scene->addItem(p);
}

void Garden::deleteZombie(Zombie* z)
{
    // qDebug()<<"Garden::deleteZombie, trying to remove Zombie";
    scene->removeItem(z);
    // qDebug()<<"come to Garden::deleteZombie after delete";
}

void Garden::deletePlant(Plant* p)
{
    // qDebug()<<"Garden::deletePlant, trying to remove Plant";
    scene->removeItem(p);
    emit destroyPlant(p);
    // p->deleteLater();
}

void Garden::destroyPea(Pea* p)
{
    // qDebug()<<"Garden::destroyPea, trying to remove pea";
    scene->removeItem(p);
    // delete(p);
    // qDebug()<<"come to Garden::destroyPea after remove";
}

// to be implemented
void Garden::produceSun(Plant* p)
{
    // qDebug()<<"come to Garden::produceSun";
    Sun* mySun = new Sun(25);
    mySun->setPos(p->pos());
    scene->addItem(mySun);
    connect(mySun,SIGNAL(emitSun(int)),this,SIGNAL(emitSun(int)));
    connect(mySun,SIGNAL(destroyMe(Sun*)),this,SLOT(destroySun(Sun*)));
}

void Garden::destroySun(Sun* s)
{
    // qDebug()<<"Garden::destroySun, trying to remove sun";
    scene->removeItem(s);
    delete(s);
}

void Garden::emitCob()
{
    prepare4Cob = true;
}

