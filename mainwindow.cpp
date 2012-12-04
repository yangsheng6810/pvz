#include <QtGui>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
// #include <QTimer>
#include "mainwindow.h"
#include "plant.h"
#include "sunflower.h"
#include "peashooter.h"
#include "backgroundmusic.h"
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

    PlantCard* card = new PlantCard("peashooter",100,20,sun);

    Field *f = new Field(sun);
    Garden *g = new Garden;

    connect(sun,SIGNAL(updateSun(int)),card,SLOT(sunUpdate(int)));
    connect(card,SIGNAL(tryPlanting(Plant*,PlantCard*)),f,SLOT(addPlant(Plant*,PlantCard*)));
    top->addWidget(card);

    card = new PlantCard("sunflower",50,15,sun);
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

    connect(removeButton, SIGNAL(clicked()),g,SLOT(prepareToRemove()));

    layout->addWidget(g);

    // QTimer::singleShot(10000, f, SLOT(removePlantDebug()));

    AllZombies* allZombies = new AllZombies();
    connect(allZombies,SIGNAL(addZombieAt(Zombie*,int,int)),g,SLOT(addZombieAt(Zombie*,int,int)));
    allZombies->addZombie(0, 0);

    layout->setSpacing(0);
    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    widget->show();
    setWindowTitle(QObject::tr("Plant VS Zombies"));
    setCentralWidget(widget);

    BackgroundMusic *music = new BackgroundMusic;
    music->startPlaying();
    this->setFixedSize(1000,700);
    // layout->setSizeConstraint(QLayout::SetFixedSize);
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
            tr("The <b>PVZ</b> was written by "
                "Yang Sheng <yangsheng6810@gmail.com>"
                " as a homework"));
}

void MainWindow::newGame()
{
    QMessageBox::information(this, tr("Not implemented!"),tr("This function hasn't been implemented!"));
}
