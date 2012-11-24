#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(plant);

    QApplication a(argc, argv);
    a.setApplicationName("PVZ");
    MainWindow w;
    w.show();
    
    return a.exec();
}
