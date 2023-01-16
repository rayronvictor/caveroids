#include "Particle.h"

Particle::Particle(Vector2 _position, Vector2 _speed, const Color& _color)
{
    color = _color;
    alpha = 1.f;
    position = _position;
    speed = _speed;
    dead = false;
}

void Particle::update(int dt)
{
    if(!dead)
    {
        position += speed * dt * SPREAD_FACTOR;
        alpha -= 0.01f;

        if(alpha <= 0.f)
            dead = true;
    }
}

void Particle::Draw()
{
    glPushMatrix();
        glLoadIdentity();

        Graphics::BeginQuads();
            Graphics::DrawRectangle(position.x, position.y, 2, 2, 0.f, color);
        Graphics::End();
    glPopMatrix();
}
