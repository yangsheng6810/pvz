#include "backgroundmusic.h"

BackgroundMusic::BackgroundMusic(QObject *parent) :
    QObject(parent)
{
    //startPlaying();
}

void BackgroundMusic::startPlaying()
{
    Phonon::MediaObject *music =
            Phonon::createPlayer(Phonon::MusicCategory,
                                 Phonon::MediaSource(":/music/Grasswalk.mp3"));
    music->play();
}
