#include "timer.h"
#include <QDebug>

Timer::Timer(qreal time, QObject *parent) :
    inteval(time*100),QObject(parent)
{
    timer = new QTimer();
    timer->setInterval(10);
    active = false;
    singleShot = false;
    paused = false;
    havingDeleted = false;
    connect(timer,SIGNAL(timeout()),this,SLOT(countDown()));
}

Timer::~Timer()
{
    if (!havingDeleted)
        timer->deleteLater();
}

void Timer::start()
{
    active = true;
    waiting = inteval;
    timer->start();
}

void Timer::start(qreal time)
{
    // qDebug()<<"in timer";
    // qDebug()<<time;
    active = true;
    inteval = time*100;
    waiting = inteval-1;
    timer->start();
}

void Timer::stop()
{
    active = false;
    timer->stop();
}

void Timer::pause()
{
    paused = true;
    if (active)
        timer->stop();
}

void Timer::restore()
{
    paused = false;
    if (active)
        timer->start();
}

void Timer::countDown()
{
    if (waiting == 0){
        emit timeout();
        if (singleShot){
            havingDeleted = true;
            delete(timer);
            // deleteLater();
        }
        else
            waiting = inteval-1;
    }
    else {
        waiting--;
    }
}

bool Timer::isSingleShot()
{
    return singleShot;
}

void Timer::setSingleShot(bool value)
{
    singleShot = value;
}
