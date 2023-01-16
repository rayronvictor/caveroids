#ifndef GAME_H
#define GAME_H

#define FLY_TIMER_SHOW 20000.f

#include "Spacecraft.h"
#include "Explosion.h"
#include "Cave.h"
#include "Sky.h"
#include "FlyingSaucer.h"
#include <QtOpenGL/QtOpenGL>

const int NUMBER_OF_ASTEROIDS = 4;

class Game
{
public:
    static int WIDTH;
    static int HEIGHT;

    Game();
    ~Game();

    void Load();
    void Draw();

    void update(int dt);
    void updateSpacecraft(int dt);
    void updateAsteroids(int dt);
    void updateExplosion(int dt);
    void updateFlyingSaucer(int dt);
    void updateSky(int dt);

    void keyPressed(QKeyEvent *event);
    void keyReleased(QKeyEvent *event);

private:
    Spacecraft *spacecraft;
    Explosion* explosion;
    Sky *sky;
    Cave *caveTop;
    Cave *caveBottom;
    FlyingSaucer *flyingSaucer;

    map<int, bool> keys;
    float flyTimerShow;                 // de quanto em quanto tempo mostra um FlyingSaucer
    bool flySmart;                      // FlyingSaucer é inteligente ou estúpido?

};

#endif // GAME_H
