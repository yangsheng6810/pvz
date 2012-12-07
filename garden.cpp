#include <QtGui>
#include <QVBoxLayout>
#include <QDebug>
#include "garden.h"
#include "zombie.h"
#include "plant.h"
#include "sunflower.h"
#include "Constants.h"
#include "pea.h"

Garden::Garden(QWidget *parent) :
    QWidget(parent), prepare(false), prepare2Remove(false)
{
    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, (COL_NUMBER+1)*GRID_X,ROW_NUMBER*GRID_Y);
    // scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/images/garden.png"));

    // view->setCacheMode(QGraphicsView::CacheBackground);
    // view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    // view->fitInView(0, 0, (COL_NUMBER+1)*GRID_X,ROW_NUMBER*GRID_Y);
    view->show();
    // view->setFixedSize((COL_NUMBER+1)*GRID_X,ROW_NUMBER*GRID_Y);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(view);
    setLayout(layout);

    QTimer* timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(1000 / 33);

}

void Garden::addPlant(Plant* plant, int row, int col)
{
    plant->setPos(actualPos(row,col));
    scene->addItem(plant);
    connect(plant,SIGNAL(emitPea(int,int,int,int)), this, SLOT(addPea(int,int,int,int)));
    connect(this,SIGNAL(sendEatTo(Plant*,int)),plant,SLOT(bitten(Plant*, int)));
    connect(plant,SIGNAL(destroyMe(Plant*)),this,SLOT(deletePlant(Plant*)));
    plant->setPlanted();
}

void Garden::removePlant(Plant* plant)
{
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
    prepare = true;
    newPlant = plant;
    // maybe some potential condition
}

void Garden::prepareToRemove()
{
    prepare2Remove = true;
}

void Garden::mousePressEvent(QMouseEvent *event)
{
    QPoint point = targetPoint(scenePos(event->pos()));
    // qDebug()<<point;
    if (event->buttons()==Qt::LeftButton){
        if (prepare){
            emit addPlantAt(newPlant,point.y(),point.x());
            prepare = false;
            newPlant = NULL;
        }
        else if (prepare2Remove){
            emit removePlantAt(point.y(),point.x());
            prepare2Remove = false;
        }
        else
            return;
    }
    else {
        // qDebug()<<"Also ignored!";
        return;
    }
}

const QPoint Garden::targetPoint(const QPointF &position) const
{
    return QPoint((position.x())/GRID_X, (position.y())/GRID_Y);
}

const QPoint Garden::scenePos(const QPointF &p) const
{
    QPointF p1(view->mapToScene(QPoint(p.x(),p.y())));
    return QPoint(p1.x()-10,p1.y()-10);// NOTE MYSTERIOUS CONSTANT!!!!!!
    /**************
      God Damn know what f**k is this!!!
      ************/
}

const QPointF Garden::actualPos(int row, int col) const
{
       QPointF p1(col*GRID_X,row*GRID_Y);
       QPointF p2(p1.x(),p1.y());
       return p2;
}

void Garden::mouseMoveEvent(QMouseEvent *event)
{
    // qDebug()<<"mouseMoveEvent goes here!";
}

void Garden::mouseReleaseEvent(QMouseEvent *event)
{
    // qDebug()<<"mouseReleaseEvent goes here!";
}

void Garden::addPea(int row, int col, int strength, int property)
{
    /*
    qDebug()<<"come to addPea in Garden";
    qDebug()<<"row "<<row<<" col "<<col;
    qDebug()<<"strength "<<strength<<" property "<<property;
    */
    Pea* p;
    if (property==3)
        p = new Pea(strength,property,"snowpea");
    else
        p = new Pea(strength,property);
    p->setPos(actualPos(row,col));
    connect(p,SIGNAL(sendHit(Zombie*,int,int)),this,SIGNAL(sendHit(Zombie*,int,int)));
    connect(p,SIGNAL(destroyMe(Pea*)),this,SLOT(destroyPea(Pea*)));
    scene->addItem(p);
}

void Garden::deleteZombie(Zombie* z)
{
    scene->removeItem(z);
    // qDebug()<<"come to Garden::deleteZombie after delete";
}

void Garden::deletePlant(Plant* p)
{
    scene->removeItem(p);
    emit destroyPlant(p);
    delete(p);
}

void Garden::destroyPea(Pea* p)
{
    // qDebug()<<"come to Garden::destroyPea";
    scene->removeItem(p);
    delete(p);
    // qDebug()<<"come to Garden::destroyPea after remove";
}
