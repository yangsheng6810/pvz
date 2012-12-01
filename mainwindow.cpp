#include <QtGui>
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTimer>
#include "mainwindow.h"
#include "plant.h"
#include "sunflower.h"
#include "peashooter.h"
#include "backgroundmusic.h"
#include "sunlight.h"
#include "field.h"
#include "allzombies.h"
#include "zombie.h"
//#include "plantcard.h"    // to be implemented

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    createActions();
    createMenus();

    SunLight *sun = new SunLight();
    // PlantCard *plantcard = new PlantCard;  // to be implemented

    QHBoxLayout *top = new QHBoxLayout;
    QVBoxLayout *layout = new QVBoxLayout;
    top->addWidget(sun);
    // top->addWidget(plantcard); // to be implemented
    layout->addLayout(top);


    Field *f = new Field;
    layout->addWidget(f);


    // the following comment out are from the first version
    /*
    Plant *pea = new Plant();
    grid->addWidget(pea,0,0);
    pea = new Plant();
    grid->addWidget(pea,1,0);

    Plant *flower = new SunFlower();
    grid->addWidget(flower,0,1);
    connect(flower,SIGNAL(produceSunLight(int)),sun,SLOT(addSunLight(int)));
    flower = new SunFlower();
    grid->addWidget(flower,1,1);
    connect(flower,SIGNAL(produceSunLight(int)),sun,SLOT(addSunLight(int)));
    */
    /*
    Plant *flower = new SunFlower();
    connect(flower,SIGNAL(produceSunLight(int)),sun,SLOT(addSunLight(int)));
    f->addPlant(flower,0,0);
    flower = new SunFlower();
    connect(flower,SIGNAL(produceSunLight(int)),sun,SLOT(addSunLight(int)));
    f->addPlant(flower,1,1);
    Plant *pea = new PeaShooter();
    f->addPlant(pea,2,2);
    pea = new PeaShooter();
    f->addPlant(pea,3,4);
    */
    Plant *flower;
    Plant *pea;
    for(int i=0; i < ROW_NUMBER; i++){
        flower = new SunFlower();
        f->addPlant(flower,i,0);
        connect(flower,SIGNAL(produceSunLight(int)),sun,SLOT(addSunLight(int)));
    }
    for(int i=0; i < ROW_NUMBER; i++){
        flower = new SunFlower();
        f->addPlant(flower,i,1);
        connect(flower,SIGNAL(produceSunLight(int)),sun,SLOT(addSunLight(int)));
    }
    for (int j=2; j < COL_NUMBER; j++)
        for(int i=0; i < ROW_NUMBER; i++){
            pea = new PeaShooter();
            f->addPlant(pea,i,j);
    }


    // the following is for debuging the first version of zombie
    /*
    Zombie *z = new Zombie();
    f->addPlant(z,3,1);
    */
    // the above lines are for debug
    QTimer::singleShot(10000, f, SLOT(removePlantDebug()));

    AllZombies* allZombies = new AllZombies();

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    widget->show();
    setWindowTitle(QObject::tr("Plant VS Zombies"));
    setCentralWidget(widget);

    BackgroundMusic *music = new BackgroundMusic;
    music->startPlaying();
}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::createMenus()
{
    gameMenu = menuBar()->addMenu(tr("&Game"));
    gameMenu->addAction(newGameAct);
    gameMenu->addSeparator();
    gameMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

void MainWindow::createActions()
{
    newGameAct = new QAction(tr("&New"),this);
    newGameAct->setShortcut(tr("Ctrl+N"));
    connect(newGameAct, SIGNAL(triggered()), this, SLOT(newGame()));

    exitAct = new QAction(tr("E&xit"),this);
    exitAct->setShortcut(tr("Ctrl+g"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

}

void MainWindow::about()
{
   QMessageBox::about(this, tr("About Application"),
            tr("The <b>PVZ</b> was written by"
                "Yang Sheng <yangsheng6810@gmail.com>"
                " and "
                " as a homework"));
}

void MainWindow::newGame()
{
    QMessageBox::information(this, tr("Not implemented!"),tr("This function hasn't been implemented!"));
}
