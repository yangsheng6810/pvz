#ifndef TIMER_H
#define TIMER_H

#include <QtCore/QObject>
#include <QtCore/QTimer>

class Timer : public QObject
{
    Q_OBJECT
public:
    explicit Timer(qreal time = 0, QObject *parent = 0);
    ~Timer();
    bool isSingleShot();
    void setSingleShot(bool value = true);
    
signals:
    void timeout();
    
public slots:
    void start();
    void start(qreal time);
    void stop();
    void pause();
    void restore();

private slots:
    void countDown();

protected:
    bool singleShot;
    bool active;
    int waiting,inteval;
    QTimer* timer;
    bool paused;
    bool havingDeleted;
};

#endif // TIMER_H
