#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <vector>
#include "Polygon.h"
#include "Vector2.h"
#include "Particle.h"

class Explosion: public Polygon
{
    public:
        Explosion(int size, Vector2 position, float force);
        ~Explosion();       // para deletar as particulas

        void Draw();
        void update(int dt);

        bool dead;

    private:
        vector<Particle*> particles;
};

#endif // EXPLOSION_H
