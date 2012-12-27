#include <QtGui>
#include <QMessageBox>
#include "mainwindow.h"
#include "plantyard.h"
#include "plant.h"
#include "sunlight.h"
#include "field.h"
#include "allzombies.h"
#include "garden.h"
#include "carddialog.h"

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

    QPushButton* pauseButton = new QPushButton(tr("Pause/\nRestore"));
    connect(pauseButton,SIGNAL(clicked()),this,SLOT(pauseOrRestore()));

    AllZombies* allZombies = new AllZombies();
    Field *f = new Field(sun, allZombies);
    allZombies->setField(f);
    Garden *g = new Garden(sun);
    yard = new PlantYard(sun,f);

    top->addWidget(yard);
    top->addWidget(removeButton);
    top->addWidget(pauseButton);
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
    connect(g,SIGNAL(explodeAt(int,int)),allZombies,SLOT(clearBox(int,int)));
    connect(allZombies,SIGNAL(youLose()),this,SLOT(youLose()));
    connect(g,SIGNAL(clearLine(int)),allZombies,SLOT(clearRow(int)));
    // connect(this,SIGNAL(sendZombies()),allZombies,SLOT(startSendZombies()));
    // allZombies->addZombie(0, 1);

    // restart
    connect(this,SIGNAL(restart()),allZombies,SLOT(restart()));
    connect(this,SIGNAL(restart()),f,SLOT(restart()));
    connect(this,SIGNAL(restart()),g,SLOT(restart()));
    connect(this,SIGNAL(restart()),yard,SLOT(restart()));
    connect(this,SIGNAL(restart()),sun,SLOT(restart()));

    // pause
    connect(this,SIGNAL(pause()),allZombies,SLOT(pause()));
    connect(this,SIGNAL(pause()),f,SLOT(pause()));
    connect(this,SIGNAL(pause()),g,SLOT(pause()));
    connect(this,SIGNAL(pause()),yard,SLOT(pause()));

    // restore
    connect(this,SIGNAL(restore()),allZombies,SLOT(restore()));
    connect(this,SIGNAL(restore()),f,SLOT(restore()));
    connect(this,SIGNAL(restore()),g,SLOT(restore()));
    connect(this,SIGNAL(restore()),yard,SLOT(restore()));


    layout->setSpacing(0);
    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    widget->show();
    setWindowTitle(QObject::tr("Plant VS Zombies"));
    setCentralWidget(widget);

    music = new BackgroundMusic;
    music->startPlaying();
    this->setFixedSize(1200,700);
    // layout->setSizeConstraint(QLayout::SetFixedSize);
    // emit sendZombies();
    paused = false;
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
    gameMenu->addAction(pauseGameAct);
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

    pauseGameAct = new QAction(tr("&Pause/Restore"),this);
    pauseGameAct->setShortcut(tr("Ctrl+P"));
    connect(pauseGameAct, SIGNAL(triggered()),this,SLOT(pauseOrRestore()));

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
    emit pause();
    CardDialog dialog(yard,this);
    int ret =dialog.exec();
    // qDebug()<<"ret of dialog"<<ret;
    if (ret == 0)
        emit restore();
    else
        emit restart();
    /*
    int ret = QMessageBox::information(this, tr("Restart Game"),
                                    tr("All current status will be lost.\n"
                                       "Are you sure to restart?"),
                                    QMessageBox::Cancel,QMessageBox::Ok);
    switch (ret){
        case QMessageBox::Ok:
            emit restart();
            break;
        case QMessageBox::Cancel:
            emit restore();
            break;
        default:
            //should never be reached
            break;
    }
    //QMessageBox::information(this, tr("Newly implemented!"),tr("This function has just implemented!"));
    */
}

void MainWindow::pauseOrRestore()
{
    if (paused)
        emit restore();
    else
        emit pause();
    paused = !paused;
}

void MainWindow::youLose()
{
    emit pause();
    int ret = QMessageBox::information(this, tr("You Lose!!"),
                                    tr("You Lose!!!\n"
                                       "Do you wish to try again?"),
                                    QMessageBox::Cancel,QMessageBox::Ok);
    /*
    switch (ret){
        case QMessageBox::Ok:
            emit restart();
            return;// added to prevent error
            break;
        case QMessageBox::Cancel:
            break;
        default:
            //should never be reached
            break;
    }
    */
    if (ret == QMessageBox::Ok){
        // emit restart();
        QTimer::singleShot(200,this,SLOT(newRestart()));
    }
}

void MainWindow::newRestart()
{
    emit restart();
    /*
    Note, this slot is used only to avoid segment fault
    in MainWindow::youLose() when emitting restart(),
    this is perhaps because of revisiting some classes
    that has already been deleted by ``restart()''
    signal.
    */
}
