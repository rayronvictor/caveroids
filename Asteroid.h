#ifndef ASTEROID_H
#define ASTEROID_H

#include "Polygon.h"
#include <list>

const float MIN_AREA     = 500.f;
const float INITIAL_SIZE = 40.f;
const float MAX_INIT_SPEED = 0.12f;
const float MIN_INIT_SPEED = 0.05f;

class Asteroid: public Polygon
{
public:
    Asteroid();
    Asteroid(float x, float y, float _angle, float _size);

    void Draw();
    void update(int dt);
    bool IsDying() const;
    bool IsDead() const;
    bool IsInSight();
    float GetSize() const;

    static list<Asteroid*> Asteroids;
    static int Count();


    Vector2 speed;

private:
    float size;
    float angularSpeed;
    float alpha;
    bool dying;
    bool dead;
};

typedef list<Asteroid*>::iterator AsteroidIter;

#endif // ASTEROID_H
