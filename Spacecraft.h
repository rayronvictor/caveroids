#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#define MAX_SPEED 30.f
#define MIN_SPEED 0.005f

#define FIRE_DELAY 200.f
#define FIRE_SPEED 0.7f

#define IMMORTALITY_DELAY 8000.f

#include "Polygon.h"
#include "Shot.h"
#include "Asteroid.h"
#include "FlyingSaucer.h"
#include <vector>

class Spacecraft : public Polygon
{
public:
    Spacecraft(float _x, float _y);
    ~Spacecraft();

    static float SPINSPEED;

    void Draw();
    void update(int dt);

    void moveForward(int dt);
    void moveBack(int dt);
    void decelerate(int dt);

    void FireShot();
    bool CollidesWith(Polygon* polygon);
    bool ShotsCollideWith(Asteroid* asteroid);
    bool CollidesWith(Polygon* polygon, float bound);
    bool CollideWithShotsOfFlyingSaucer(FlyingSaucer* flyingSaucer);
    void GotHit();
    bool IsHit() const;

    Vector2 speed;
    int lives;

private:    
    Vector2 acceleration;
    bool powered;
    bool isHit;
    float immortalityTimer;

    vector<Shot*> shots;
    float fireTimer;
};

#endif // SPACECRAFT_H
