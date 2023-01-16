#ifndef SHOT_H
#define SHOT_H

const float SHOT_LENGTH = 10.f;
const float SHOT_DURATION = 1000;

#include "Polygon.h"

class Shot: public Polygon
{
public:
    Shot();
    Shot(float x, float y, const Vector2& _speed, const Color& _color);

    void Draw();
    void update(int dt);
    Vector2 GetDirection();

    Vector2 speed;
    Vector2 direction;
    int lifeTime;

};

#endif // SHOT_H
