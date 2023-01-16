#include "Shot.h"
#include "Game.h"

Shot::Shot()
{
    color = Color::Green;
    position.Zero();
    speed.Zero();
    direction.Zero();
    lifeTime = SHOT_DURATION;
}

Shot::Shot(float x, float y, const Vector2& _speed, const Color& _color)
{
    color = _color;
    position.x = x;
    position.y = y;
    speed = _speed;
    direction.x = SHOT_LENGTH * Math::Cos(speed.GetAngle());
    direction.y = SHOT_LENGTH * Math::Sin(-speed.GetAngle());
    lifeTime = SHOT_DURATION;
}

void Shot::Draw()
{
    glLoadIdentity();

    glLineWidth(5.f);

    Graphics::BeginLines();
        glColor4f(color.R, color.G, color.B, color.A);
        glVertex2f(position.x, position.y);
        glVertex2f(position.x + direction.x, position.y + direction.y);
    Graphics::End();

    glLineWidth(2.f);
}

void Shot::update(int dt)
{
    position += speed * dt;

    if(position.x < 0)
        position.x = Game::WIDTH;
    if(position.y < 0)
        position.y = Game::HEIGHT;
    if(position.x > Game::WIDTH)
        position.x = 0;
    if(position.y > Game::HEIGHT)
        position.y = 0;

    lifeTime -= dt;
}

Vector2 Shot::GetDirection()
{
    return direction;
}

