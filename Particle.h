#ifndef PARTICLE_H
#define PARTICLE_H

#define SPREAD_FACTOR 0.1f

#include "Polygon.h"
#include "Vector2.h"
#include "Color.h"

class Particle: public Polygon
{
    public:
        Particle(Vector2 _position, Vector2 _speed, const Color& _color);

        void Draw();
        void update(int dt);

    public:
        Color color;
        float alpha;
        Vector2 position;
        Vector2 speed;
        bool dead;
};

#endif // PARTICLE_H
