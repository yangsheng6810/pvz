#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QGridLayout>
#include "Constants.h"
#include "plant.h"

class Field : public QWidget
{
    Q_OBJECT
public:
    explicit Field(QWidget *parent = 0);

private:
    Plant* plantField[ROW_NUMBER][COL_NUMBER];
    //QWidget* plantField[ROW_NUMBER][COL_NUMBER];
    QGridLayout* grid;// not a good idea
signals:
    void sendPea(int row, int col, int type);// type is used for potential useage
    // maybe sendWatermelon
    void plantSucceed(QString plantName);
public slots:
    void addPlant(Plant *plant, int row, int col);
    void removePlant(int row, int col);
    void removePlantDebug(void);

};

#endif // FIELD_H
