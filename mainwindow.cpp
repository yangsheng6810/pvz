#include <QtGui>
#include "mainwindow.h"
#include "plant.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    createActions();
    createMenus();
    QPushButton *quit = new QPushButton(tr("Quit"));
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    QGridLayout *grid = new QGridLayout;
    Plant *pea = new Plant;
    grid->addWidget(pea,0,0);
    Plant *pea1 = new Plant;
    grid->addWidget(pea1,0,1);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(quit);
    layout->addLayout(grid);
    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    widget->show();
    setWindowTitle(QObject::tr("Plant VS Zombies"));
    setCentralWidget(widget);
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
