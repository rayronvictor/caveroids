#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QGLWidget>
#include <QTimer>
#include "Game.h"

class MainPanel : public QGLWidget
{
    Q_OBJECT
public:
    explicit MainPanel(QWidget *parent = 0);

signals:

public slots:
    void atualizar();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    QTimer *timer;
    int currentTime;
    int previousTime;
    Game *game;

};

#endif // MAINPANEL_H
