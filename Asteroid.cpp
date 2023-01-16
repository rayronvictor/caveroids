#include "Asteroid.h"
#include "Game.h"

list<Asteroid*> Asteroid::Asteroids;

Asteroid::Asteroid()
{
    speed.Zero();
    angularSpeed = Math::Random(-MAX_INIT_SPEED, MAX_INIT_SPEED);
    alpha = 1.f;
    dying = false;
    dead = false;
    size = 0.f;
    color = Color::Gray;
}

Asteroid::Asteroid(float x, float y, float _angle, float _size)
{
    speed.x = Math::Random(MIN_INIT_SPEED, MAX_INIT_SPEED) * Math::Cos(Math::Random(0.f, 359.f));
    speed.y = Math::Random(MIN_INIT_SPEED, MAX_INIT_SPEED) * Math::Sin(Math::Random(0.f, 359.f));

    angularSpeed = Math::Random(-MAX_INIT_SPEED, MAX_INIT_SPEED);
    alpha = 1.f;
    dying = false;
    dead = false;
    size = Math::Clamp(_size, 0.f, _size);
    color = Color::Gray;

    Vector2 vertex;

    for(int i = 0; i < 6; ++i)
    {
        vertex.x = x + _size * Math::Cos(i * 60.f + Math::Random(10.f, 30.f));
        vertex.y = y + _size * Math::Sin(i * 60.f + Math::Random(10.f, 30.f));

        AddVertex(vertex);
    }
}

void Asteroid::Draw()
{
    if(vertices.size() < 3) return;

    glLoadIdentity();

    Graphics::BeginLineLoop();
            glColor4f(color.R, color.G, color.B, alpha);
            for(unsigned int i = 0; i < vertices.size(); ++i) glVertex2f(vertices[i].x, vertices[i].y);
    Graphics::End();
}

void Asteroid::update(int dt)
{
    angle += angularSpeed;

    float x, y = 0;

    // Roda os pontos
    for(unsigned int i = 0; i < vertices.size(); ++i)
    {
        x = position.x + Math::Cos(angularSpeed) * (vertices[i].x - position.x) - Math::Sin(angularSpeed) * (vertices[i].y - position.y);
        y = position.y + Math::Sin(angularSpeed) * (vertices[i].x - position.x) + Math::Cos(angularSpeed) * (vertices[i].y - position.y);

        vertices[i].x = x;
        vertices[i].y = y;

        vertices[i] += speed * dt;
    }

    position = GetCenter();

    if(position.x + INITIAL_SIZE < 0 && speed.x < 0.f)
    {
        for(unsigned int i = 0; i < vertices.size(); ++i)    vertices[i].x += (Game::WIDTH + INITIAL_SIZE * 2);
    }
    if(position.x - INITIAL_SIZE > Game::WIDTH && speed.x > 0.f)
    {
        for(unsigned int i = 0; i < vertices.size(); ++i)    vertices[i].x -= (Game::WIDTH + INITIAL_SIZE * 2);
    }
    if(position.y + INITIAL_SIZE < 0 && speed.y < 0.f)
    {
        for(unsigned int i = 0; i < vertices.size(); ++i)   vertices[i].y += (Game::HEIGHT + INITIAL_SIZE * 2);
    }
    if(position.y - INITIAL_SIZE > Game::HEIGHT && speed.y > 0.f)
    {
        for(unsigned int i = 0; i < vertices.size(); ++i)   vertices[i].y -= (Game::HEIGHT + INITIAL_SIZE * 2);
    }

    if(!dying && !dead)
    {
        if(GetArea() < MIN_AREA) dying = true;
    }
    else if(dying && !dead)
    {
        alpha -= 0.002f * dt;

        if(alpha <= 0.f)
        {
            dead = true;
            dying = false;
        }
    }
}

bool Asteroid::IsDying() const
{
    return dying;
}

bool Asteroid::IsDead() const
{
    return dead;
}

bool Asteroid::IsInSight()
{
    for(unsigned int i = 0; i < vertices.size(); ++i)
    {
        // se apenas um ponto está na tela, o asteróide deve ser visível
        if(Math::PointInsideRectangle(vertices[i], 0, Game::WIDTH, 0, Game::HEIGHT))
            return true;
    }

    return false;
}

float Asteroid::GetSize() const
{
    return size;
}

int Asteroid::Count()
{
    return (Asteroid::Asteroids.size());
}
