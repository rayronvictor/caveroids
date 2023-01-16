#include "FlyingSaucer.h"

FlyingSaucer::FlyingSaucer(bool _smart)
{
    speed = Vector2(FLY_SPEED, 0.f);
    color = Color::LightBlue;
    smart = _smart;
    shots.clear();
    dead = false;

    AddVertex(Vector2(-30.f, 5.f ));
    AddVertex(Vector2(-15.f, 10.f));
    AddVertex(Vector2(15.f, 10.f));
    AddVertex(Vector2(30.f, 5.f));
    AddVertex(Vector2(30.f, -5.f));
    AddVertex(Vector2(15.f, -10.f));
    AddVertex(Vector2(-15.f, -10.f));
    AddVertex(Vector2(-30.f, -5.f));

    for(unsigned int i = 0; i < vertices.size(); ++i)
        vertices[i] += Vector2(0.f, 300.f);
}

void FlyingSaucer::Draw()
{
    glPushMatrix();
        glLoadIdentity();

        for(unsigned int i = 0; i < shots.size(); ++i)
        {
            if(shots[i]) shots[i]->Draw();
        }

        glLoadIdentity();

        glTranslated(position.x, position.y, 0.f);

        if(smart)  glScalef(0.7, 0.7f, 0.f);
        else       glScalef(1.f, 1.f, 0.f);

        glTranslated(-position.x, -position.y, 0.0);

        Graphics::BeginPolygons();
                glColor4f(color.R, color.G, color.B, color.A);
                for(unsigned int i = 0; i < vertices.size(); ++i) glVertex2f(vertices[i].x, vertices[i].y);
        Graphics::End();

        Color c = Color::DarkBlue;
        Graphics::DrawRectangle(vertices[vertices.size()-1].x, vertices[vertices.size()-1].y, 60.f, 10.f, 0.f, c);
     glPopMatrix();
}

void FlyingSaucer::update(int dt)
{

    //if(position.y == 0.f) position.y = 300.f;

    if(smart)
    {
        angle += RATE_OF_OSCILLATION_SMART;
        speed.y = Math::Cos(angle) * AMPLITUDE;
    }
    else
    {
        speed.y = 0.01f;
    }

    // Roda os pontos
    for(unsigned int i = 0; i < vertices.size(); ++i)
    {
        vertices[i].x += speed.x * dt;
        vertices[i].y += speed.y * dt;
    }

    position += speed * dt;

    if(fireTimer >= 0) fireTimer -= dt;

    // Atualiza os tiros
    for(unsigned int i = 0; i < shots.size(); ++i)
    {
        if(shots[i])
        {
            if(shots[i]->lifeTime < 0)
            {
                delete shots[i];
                shots.erase(shots.begin() + i);
                --i;
            }
            else
            {
                shots[i]->update(dt);
            }
        }
    }
}

void FlyingSaucer::FireShot(Polygon *spacecraft)
{
    if(fireTimer <= 0.f)
    {
        Shot* shot;

        if(smart)
        {
            Vector2 a(spacecraft->position.x - position.x, spacecraft->position.y - position.y);
            shot = new Shot(position.x, position.y,
                            Vector2(FLY_FIRE_SPEED_SMART * Math::Cos(a.GetAngle()), -FLY_FIRE_SPEED_SMART * Math::Sin(a.GetAngle()) ),
                            Color::Gold);
        }
        else
        {
            shot = new Shot(position.x, position.y,
                            Vector2(FLY_FIRE_SPEED_DUMB * Math::Cos(Math::Random(0.f, 359.f)), FLY_FIRE_SPEED_DUMB * Math::Sin(Math::Random(0.f, 359.f)) ),
                            Color::Yellow);
        }

        shots.push_back(shot);

        if(smart)
            fireTimer = FLY_FIRE_DELAY_SMART;
        else
            fireTimer = FLY_FIRE_DELAY_DUMB;
    }
}

bool FlyingSaucer::IsDead()
{
    return dead;
}

