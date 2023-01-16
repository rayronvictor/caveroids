#include "MainPanel.h"
#include <QTime>
#include <iostream>

MainPanel::MainPanel(QWidget *parent) :
    QGLWidget(parent)
{
    setFocus();
    setFormat(QGL::DoubleBuffer | QGL::DepthBuffer);

    game = new Game();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(atualizar()));
    timer->start(33);

    currentTime = QTime::currentTime().msec();

}

void MainPanel::atualizar()
{
    previousTime = currentTime;
    currentTime = QTime::currentTime().msec();

    if(currentTime < previousTime)
    {
        game->update(currentTime - (previousTime - 1000));
    }
    else
    {
        game->update(currentTime - previousTime);
    }

    updateGL();
}

void MainPanel::initializeGL()
{
    Color c = Color::Black;
    Graphics::SetClearColor(c);
}

void MainPanel::resizeGL(int width, int height)
{
    Graphics::Set2dMode(width, height);
}

void MainPanel::paintGL()
{
    Graphics::ClearScreen();    // limpa a janela de visualização
    glLoadIdentity();           // limpa todas as transformações

    game->Draw();
}

void MainPanel::keyPressEvent(QKeyEvent *event)
{
    game->keyPressed(event);
}

void MainPanel::keyReleaseEvent(QKeyEvent *event)
{
    game->keyReleased(event);
}
