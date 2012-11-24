#ifndef BACKGROUNDMUSIC_H
#define BACKGROUNDMUSIC_H

#include <QObject>
#include <MediaObject>

class BackgroundMusic : public QObject
{
    Q_OBJECT
public:
    explicit BackgroundMusic(QObject *parent = 0);
    void startPlaying();
signals:
    
public slots:

protected:
};

#endif // BACKGROUNDMUSIC_H
