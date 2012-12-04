#include <QtGui>
#include <QVBoxLayout>
#include <QDebug>
#include "garden.h"
#include "zombie.h"
#include "plant.h"
#include "sunflower.h"
#include "Constants.h"

Garden::Garden(QWidget *parent) :
    QWidget(parent), prepare(false)
{
    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, 600, 400);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    Zombie *z1 = new Zombie;
    z1->setPos(300,100);
    scene->addItem(z1);
    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/images/garden.png"));

    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    // view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->resize(400,300);
    view->show();
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(view);
    setLayout(layout);
    setMouseTracking(true);

    // SunFlower *p = new SunFlower;
    // p->setPos(0,0);
    // scene->addItem(p);

    QTimer* timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(1000 / 33);

}

void Garden::addPlant(Plant* plant, int row, int col)
{
    plant->setPos(row*80,col*100);
    scene->addItem(plant);
}

void Garden::removePlant(Plant* plant)
{
    scene->removeItem(plant);
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
    if (event->buttons()==Qt::LeftButton){
        if (prepare){
            QPoint point = targetPoint(event->pos());
            emit addPlantAt(newPlant,point.x(),point.y());
            prepare = false;
            newPlant = NULL;
        }
        else if (prepare2Remove){
            QPoint point = targetPoint(event->pos());
            emit removePlantAt(point.x(),point.y());
            prepare2Remove = false;
        }
        else
            return;
    }
    else {
        qDebug()<<"Also ignored!";
        return;
    }
}

const QPoint Garden::targetPoint(const QPoint &position) const
{
    return QPoint(position.x()/GRID_X, position.y()/GRID_Y);
}

void Garden::mouseMoveEvent(QMouseEvent *event)
{
    // qDebug()<<"mouseMoveEvent goes here!";
}

void Garden::mouseReleaseEvent(QMouseEvent *event)
{
    // qDebug()<<"mouseReleaseEvent goes here!";
}

