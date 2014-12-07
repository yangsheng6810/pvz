#ifndef CARDDIALOG_H
#define CARDDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLCDNumber>
#include "plantcard.h"
#include "plantyard.h"

class CardDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CardDialog(PlantYard* yy,QWidget *parent = 0);
    QGridLayout* layout;
    
signals:
    
public slots:
    void addCard(QString name,int cost, int time);
    void okClicked();
    void cancelClicked();
    void prepareCard(int pp);

protected:
    int row, col;
    QString allName[3][6];
    bool chosenName[3][6];
    QString cards[9];
    QSignalMapper* mapper;
    int counter;
    int cost[3][6];
    int time[3][6];
    PlantYard* yard;
    QLCDNumber* lcd;
};

#endif // CARDDIALOG_H
