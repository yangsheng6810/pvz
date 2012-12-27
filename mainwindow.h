#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "backgroundmusic.h"
class PlantYard;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    // QSize sizeHint() const;
    ~MainWindow();

signals:
    void sendZombies();
    void restart();
    void pause();
    void restore();

private slots:
    void newGame();
    void pauseOrRestore();
    void about();
    void youLose();
    void newRestart();

private:
    QMenu *gameMenu;
    QMenu *helpMenu;
    QAction *newGameAct;
    QAction *pauseGameAct;
    QAction *exitAct;
    QAction *aboutAct;
    void createMenus();
    void createActions();
    BackgroundMusic *music;
    bool paused;
    PlantYard* yard;

};

#endif // MAINWINDOW_H
