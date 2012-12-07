#include <QtGui>
#include <QMessageBox>
// #include <QTimer>
#include "mainwindow.h"
#include "plant.h"
#include "sunflower.h"
#include "peashooter.h"
#include "sunlight.h"
#include "field.h"
#include "allzombies.h"
#include "zombie.h"
#include "garden.h"
#include "plantcard.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    createActions();
    createMenus();

    setMouseTracking(true);

    SunLight *sun = new SunLight();

    QHBoxLayout *top = new QHBoxLayout;
    QVBoxLayout *layout = new QVBoxLayout;
    top->addWidget(sun);

    QPixmap* pixmap = new QPixmap(":/images/remove.png");
    QPushButton* removeButton = new QPushButton;
    removeButton->setIcon(QIcon(*pixmap));
    removeButton->setIconSize(pixmap->rect().size());

    PlantCard* card = new PlantCard("peashooter",100,30,sun);

    AllZombies* allZombies = new AllZombies();
    Field *f = new Field(sun, allZombies);
    Garden *g = new Garden;

    connect(sun,SIGNAL(updateSun(int)),card,SLOT(sunUpdate(int)));
    connect(card,SIGNAL(tryPlanting(Plant*,PlantCard*)),f,SLOT(addPlant(Plant*,PlantCard*)));
    top->addWidget(card);

    card = new PlantCard("sunflower",50,15,sun);
    connect(sun,SIGNAL(updateSun(int)),card,SLOT(sunUpdate(int)));
    connect(card,SIGNAL(tryPlanting(Plant*,PlantCard*)),f,SLOT(addPlant(Plant*,PlantCard*)));
    top->addWidget(card);

    card = new PlantCard("wallNut",50,200,sun);
    connect(sun,SIGNAL(updateSun(int)),card,SLOT(sunUpdate(int)));
    connect(card,SIGNAL(tryPlanting(Plant*,PlantCard*)),f,SLOT(addPlant(Plant*,PlantCard*)));
    top->addWidget(card);

    card = new PlantCard("snowPea",175,100,sun);
    connect(sun,SIGNAL(updateSun(int)),card,SLOT(sunUpdate(int)));
    connect(card,SIGNAL(tryPlanting(Plant*,PlantCard*)),f,SLOT(addPlant(Plant*,PlantCard*)));
    top->addWidget(card);

    card = new PlantCard("splitPea",125,100,sun);
    connect(sun,SIGNAL(updateSun(int)),card,SLOT(sunUpdate(int)));
    connect(card,SIGNAL(tryPlanting(Plant*,PlantCard*)),f,SLOT(addPlant(Plant*,PlantCard*)));
    top->addWidget(card);

    card = new PlantCard("jalapeno",125,200,sun);
    connect(sun,SIGNAL(updateSun(int)),card,SLOT(sunUpdate(int)));
    connect(card,SIGNAL(tryPlanting(Plant*,PlantCard*)),f,SLOT(addPlant(Plant*,PlantCard*)));
    top->addWidget(card);

    card = new PlantCard("threepeater",325,100,sun);
    connect(sun,SIGNAL(updateSun(int)),card,SLOT(sunUpdate(int)));
    connect(card,SIGNAL(tryPlanting(Plant*,PlantCard*)),f,SLOT(addPlant(Plant*,PlantCard*)));
    top->addWidget(card);


    top->addWidget(removeButton);
    layout->addLayout(top);


    connect(f,SIGNAL(addPlantPic(Plant*,int,int)),g,SLOT(addPlant(Plant*,int,int)));
    connect(f,SIGNAL(removePlantPic(Plant*)),g,SLOT(removePlant(Plant*)));
    connect(f,SIGNAL(prepareToPlant(Plant*)),g,SLOT(prepareToPlant(Plant*)));
    connect(g,SIGNAL(addPlantAt(Plant*,int,int)),f,SLOT(addPlant(Plant*, int,int)));
    connect(f,SIGNAL(subSun(int)),sun,SLOT(subtractSunLight(int)));
    connect(g,SIGNAL(removePlantAt(int,int)),f,SLOT(removePlant(int,int)));
    connect(g,SIGNAL(destroyPlant(Plant*)),f,SLOT(deletePlant(Plant*)));

    connect(removeButton, SIGNAL(clicked()),g,SLOT(prepareToRemove()));

    layout->addWidget(g);

    // QTimer::singleShot(10000, f, SLOT(removePlantDebug()));

    connect(allZombies,SIGNAL(addZombieAt(Zombie*,int,int)),g,SLOT(addZombieAt(Zombie*,int,int)));
    connect(g,SIGNAL(sendHit(Zombie*,int,int)),allZombies,SIGNAL(receiveHit(Zombie*,int,int)));
    connect(allZombies,SIGNAL(deleteZombie(Zombie*)),g,SLOT(deleteZombie(Zombie*)));
    // connect(this,SIGNAL(sendZombies()),allZombies,SLOT(startSendZombies()));
    // allZombies->addZombie(0, 1);

    layout->setSpacing(0);
    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    widget->show();
    setWindowTitle(QObject::tr("Plant VS Zombies"));
    setCentralWidget(widget);

    music = new BackgroundMusic;
    music->startPlaying();
    this->setFixedSize(1000,700);
    // layout->setSizeConstraint(QLayout::SetFixedSize);
    // emit sendZombies();
}

MainWindow::~MainWindow()
{
    delete(gameMenu);
    delete(helpMenu);
    delete(music);
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
            tr("The <b>PVZ</b> was written by "
                "Yang Sheng <yangsheng6810@gmail.com>"
                " as a homework"));
}

void MainWindow::newGame()
{
    QMessageBox::information(this, tr("Not implemented!"),tr("This function hasn't been implemented!"));
}
