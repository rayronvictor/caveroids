#include "Explosion.h"

Explosion::Explosion(int size, Vector2 position, float force)
{
    float angleStep = 360.f / (float)size;

    for(int i = 0; i < size; ++i)
    {
        Particle* particle = new Particle(position, Vector2(1.f, 1.f) * force, Color::Orange);
        particle->speed *= Vector2(Math::Cos(angleStep * i) * Math::Random(1.f, 2.f), Math::Sin(angleStep * i) * Math::Random(1.f, 2.f));
        particles.push_back(particle);
    }

    dead = false;
}

Explosion::~Explosion()
{
    for(unsigned int i = 0; i < particles.size(); ++i)
    {
        if(particles[i]) delete particles[i];
    }

    particles.clear();
}

void Explosion::update(int dt)
{
    if(!dead)
    {
        for(vector<Particle*>::iterator it = particles.begin(); it != particles.end();)
        {
            if((*it)->dead)
            {
                delete (*it);
                it = particles.erase(it);
            }
            else
            {
                if((*it)) (*it)->update(dt);
                ++it;
            }
        }

        if(particles.empty()) dead = true;
    }
}

void Explosion::Draw()
{
    for(unsigned int i = 0; i < particles.size(); ++i)   particles[i]->Draw();
}
