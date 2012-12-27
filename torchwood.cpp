#include "torchwood.h"
#include <QList>
#include "pea.h"

Torchwood::Torchwood(QObject *parent) :
    Plant("torchwood")
{
}

void Torchwood::advance(int step)
{
    Plant::advance(step);
    if (!planted)
        return;
    QList<QGraphicsItem *>list = collidingItems();
    Pea* pp;
    for (int i = 0; i < list.size(); ++i){
        pp = qgraphicsitem_cast<Pea* >(list.at(i));
        if (pp && pp->getProperty()<=3)
            pp->setProperty(2);
    }
}
