#ifndef FLYINGSAUCER_H
#define FLYINGSAUCER_H

#define FLY_HEIGHT 5.f
#define FLY_WIDTH 40.f

#define FLY_SPEED 0.05f
#define RATE_OF_OSCILLATION_SMART 5.f;
#define RATE_OF_OSCILLATION_DUMB 0.01f;
#define AMPLITUDE 0.2f

#define FLY_FIRE_DELAY_SMART 1000.f
#define FLY_FIRE_DELAY_DUMB 600.f
#define FLY_FIRE_SPEED_SMART 0.3f
#define FLY_FIRE_SPEED_DUMB 0.6f

#include "Polygon.h"
#include "Shot.h"

class FlyingSaucer: public Polygon
{
public:
    FlyingSaucer(bool _smart);
    void Draw();
    void update(int dt);
    void FireShot(Polygon *spacecraft);
    bool IsDead();

    Vector2 speed;
    vector<Shot*> shots;

private:
    bool smart;
    bool dead;    
    float fireTimer;
};

#endif // FLYINGSAUCER_H
