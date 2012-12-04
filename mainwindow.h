#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QLCDNumber>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    // QSize sizeHint() const;
    ~MainWindow();

private slots:
    void newGame();
    void about();

private:
    QMenu *gameMenu;
    QMenu *helpMenu;
    QAction *newGameAct;
    QAction *exitAct;
    QAction *aboutAct;
    void createMenus();
    void createActions();
};

#endif // MAINWINDOW_H
