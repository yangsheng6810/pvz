#include "field.h"
// #include <QGridLayout> // included in head file
#include <QRect>
#include <QPoint>
#include <QDebug>

Field::Field(QWidget *parent) :
    QWidget(parent)
{
    // setMinimumSize(600, 800);
    // setMaximumSize(600, 800);
    grid= new QGridLayout;
    grid->setGeometry(QRect(QPoint(0,0),QPoint(600,800)));
    this->setLayout(grid);
    for(int i=0; i < ROW_NUMBER; i++)
        for(int j = 0; j < COL_NUMBER; j++)
            plantField[i][j]=NULL;

}


void Field::addPlant(Plant* plant, int row, int col)
{
    if (plant != 0) {
        if (row >= ROW_NUMBER || col >= COL_NUMBER){
            qDebug() << QString("Exceeds!")<<ROW_NUMBER<<" "<<row<<" "<<COL_NUMBER<<" "<<col;
        }
        plantField[row][col] = plant;
        grid->addWidget(plant,row,col);
    }
}

void Field::removePlant(int row, int col)
{
    if (plantField[row][col] != 0) {
        grid->removeWidget(plantField[row][col]);
        delete(plantField[row][col]);
        plantField[row][col] = 0;
    }
}

void Field::removePlantDebug()
{
    removePlant(3,0);
}
