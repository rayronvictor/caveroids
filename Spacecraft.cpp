#include "Spacecraft.h"
#include "Game.h"
#include <iostream>

float Spacecraft::SPINSPEED = 0.3f; // velocidade de giro

Spacecraft::Spacecraft(float _x, float _y)
{
    position = Vector2(_x, _y);
    speed = Vector2(0.f, 0.f);
    acceleration = Vector2(0.02f, 0.02f);

    lives = 10;
    angle = 0.f;
    area = 0.f;
    color = Color::White;
    isHit = false;
    immortalityTimer = IMMORTALITY_DELAY;

    vertices.clear();
    shots.clear();

    fireTimer = 0.f;
    powered = false;
}

Spacecraft::~Spacecraft()
{
    for(unsigned int i = 0; i < shots.size(); ++i)
    {
        if(shots[i]) delete shots[i];
    }

    shots.clear();
}

void Spacecraft::Draw()
{
    glPushMatrix();
        glLoadIdentity();

        for(unsigned int i = 0; i < shots.size(); ++i)
        {
            if(shots[i]) shots[i]->Draw();
        }

        glLoadIdentity();

        glTranslated(position.x, position.y, 0.f);
        glRotatef(angle, 0.0, 0.0, 1.0);
        glTranslated(-position.x, -position.y, 0.0);

        glLineWidth(1.0);

        if(isHit)
        {
            Color fieldColor = Color::LightBlue;
            Graphics::DrawCircle(position.x, position.y, 40.f, fieldColor);
            for(unsigned int i = 0; i < 5; ++i)
            {
                float rnd = rand() % 20 + 20.f;
                Graphics::DrawCircle(position.x, position.y, rnd, fieldColor);
            }
        }

        // desenha o fogo
        if(powered)
        {
            // números randômicos para variar o fogo
            float rndLeft     = rand() % 5 + 5; // 3 - 8
            float rndMiddle   = rand() % 5 + 10; // 8 - 13
            float rndRight    = rand() % 5 + 5; // 3 - 8

            // tamanho do fogo com base na velocidade
            float fireLenght = speed.Length() * 0.1f;

            // cor do fogo
            Color fireColor(1.f, 0.49f, 0.15f, 1.f);

            // fogo esquerdo
            Graphics::DrawLine(position.x - 7.f, position.y - 8.f,
                               position.x - rndLeft - 12.5f * fireLenght, position.y, fireColor);
            Graphics::DrawLine(position.x - rndLeft - 12.5f * fireLenght, position.y,
                               position.x - 7.f, position.y, fireColor);

            // fogo do meio
            Graphics::DrawLine(position.x - 7.f, position.y - 4.f,
                               position.x - rndMiddle - 12.5f * fireLenght, position.y, fireColor);
            Graphics::DrawLine(position.x - rndMiddle - 12.5f * fireLenght, position.y,
                               position.x - 7.f, position.y + 4.f, fireColor);

            // fogo direito
            Graphics::DrawLine(position.x - 7.f, position.y,
                               position.x - rndRight - 12.5f * fireLenght, position.y, fireColor);
            Graphics::DrawLine(position.x - rndRight - 12.5f * fireLenght, position.y,
                               position.x - 7.f, position.y + 8.f, fireColor);

        }

        glLineWidth(1.5);

        // desenha a nave

        // aresta subindo
        Graphics::DrawLine(position.x - 15.f, position.y - 10.f,
                           position.x + 15.f, position.y + 0.f, color);
        // aresta descendo
        Graphics::DrawLine(position.x + 15.f, position.y + 0.f,
                           position.x - 15.f, position.y + 10.f, color);
        // aresta horizontal
        Graphics::DrawLine(position.x - 9.f, position.y - 8.f,
                           position.x - 9.f, position.y + 8.f, color);


    glPopMatrix();
}

void Spacecraft::moveForward(int dt)
{
    powered = true;

    if(speed.x < MAX_SPEED && speed.x > -MAX_SPEED)
    {
        speed.x += acceleration.x * cos(GetAngle() * Math::Degs2Rads) * dt;
    }

    if(speed.y < MAX_SPEED && speed.y > -MAX_SPEED)
    {
        speed.y += acceleration.y * sin(GetAngle() * Math::Degs2Rads) * dt;
    }
}

void Spacecraft::moveBack(int dt)
{
    powered = true;

    if(speed.x > -MAX_SPEED)
    {
        speed.x -= acceleration.x * cos(angle * Math::Degs2Rads) * dt;
    }

    if(speed.y > -MAX_SPEED)
    {
         speed.y -= acceleration.y * sin(angle * Math::Degs2Rads) * dt;
    }
}

void Spacecraft::decelerate(int dt)
{
    powered = false;

    if( (speed.x > MIN_SPEED || speed.y > MIN_SPEED) || (speed.x < -MIN_SPEED || speed.y < -MIN_SPEED))
    {
        speed.x *= 1 - acceleration.x;
        speed.y *= 1 - acceleration.y;
    }
    else
        speed.Zero();
}

void Spacecraft::FireShot()
{
    if(fireTimer <= 0.f)
    {
        Shot* shot = new Shot(position.x, position.y,
                              Vector2(FIRE_SPEED * Math::Cos(GetAngle()), FIRE_SPEED * Math::Sin(GetAngle()) ),
                              Color::Green);
        shots.push_back(shot);
        fireTimer = FIRE_DELAY;
    }
}

bool Spacecraft::CollidesWith(Polygon* polygon)
{
    if(polygon->PointInPolygon(position.x + 10.f, position.y) ||
               polygon->PointInPolygon(position.x - 10.f, position.y + 10.f) ||
               polygon->PointInPolygon(position.x - 5.f, position.y) ||
               polygon->PointInPolygon(position.x - 10.f, position.y - 10.f))
        return true;
    return false;
}

bool Spacecraft::CollidesWith(Polygon* polygon, float bound)
{
    if(polygon->PointInPolygon(position.x + bound, position.y) ||
               polygon->PointInPolygon(position.x - bound, position.y + bound) ||
               polygon->PointInPolygon(position.x - bound / 2.f, position.y) ||
               polygon->PointInPolygon(position.x - bound, position.y - bound))
        return true;
    return false;
}

bool Spacecraft::CollideWithShotsOfFlyingSaucer(FlyingSaucer* flyingSaucer)
{
    for(vector<Shot*>::iterator itr = flyingSaucer->shots.begin(); itr != flyingSaucer->shots.end();)
    {
        if((*itr))
        {
            if((*itr)->position.x >= position.x - 20.f && (*itr)->position.x < position.x + 20.f &&
               (*itr)->position.y >= position.y - 20.f && (*itr)->position.y < position.y + 20.f)
            {
                return true;
            }
            else
            {
                ++itr;
            }
        }
    }
    return false;
}

bool Spacecraft::ShotsCollideWith(Asteroid* asteroid)
{
    if(!asteroid)
        return false;

    Vector2 vertex1;
    Vector2 vertex2;
    Asteroid* asteroid1 = NULL;
    Asteroid* asteroid2 = NULL;
    int ni = 0; // próximo indice
    int side = 0;
    int nextSide = 0;
    Vector2 point;
    Vector2 endpoint;
    Vector2 dir;

    // loop através de todos os tiros
    for(vector<Shot*>::iterator itr = shots.begin(); itr != shots.end();)
    {
        if((*itr))
        {
            // guarda o início e fim do tiro atual
            point = (*itr)->position;
            dir = (*itr)->GetDirection();
            endpoint = point + dir;

            // se uma ou outra extremidade do tiro está dentro do asteróide, então ele colidiu
            if(asteroid->PointInPolygon(point) || asteroid->PointInPolygon(endpoint))
            {
                // cria 2 novos asteroids
                asteroid1 = new Asteroid();
                asteroid2 = new Asteroid();

                // guarda o resultado da intersecção
                Vector2 tempVector;

                // percorre os vértices do asteroid
                for(unsigned int v = 0; v < asteroid->vertices.size(); ++v)
                {
                    // pega o próximo indice. com circulação
                    ni = (v + 1 == asteroid->vertices.size()) ? 0 : v + 1;

                    vertex1.x = asteroid->vertices[v].x;
                    vertex1.y = asteroid->vertices[v].y;
                    vertex2.x = asteroid->vertices[ni].x;
                    vertex2.y = asteroid->vertices[ni].y;

                    side = Math::PointSideOfLine(vertex1, point, endpoint);
                    nextSide = Math::PointSideOfLine(vertex2, point, endpoint);

                    // vértices são distribuídos arbitrariamente
                    if(side == 1)
                    {
                        asteroid1->AddVertex(asteroid->vertices[v]);
                    }
                    else
                    {
                        asteroid2->AddVertex(asteroid->vertices[v]);
                    }

                    // os dois pontos atuais estavam em lados diferentes das extremidades do tiro
                    if(side != nextSide)
                    {
                        Vector2 vertexTemp(vertex2 - vertex1);
                        tempVector = Math::VectorLineIntersection(point, dir, vertex1, vertexTemp);

                        asteroid1->AddVertex(tempVector);
                        asteroid2->AddVertex(tempVector);
                    }
                }

                // gera um novo asteroid baseado na velocidade do tiro
                //asteroid1->speed = Vector2((*itr)->speed.x, -(*itr)->speed.y) * 0.1f;
                //asteroid2->speed = Vector2((*itr)->speed.x, (*itr)->speed.y) * 0.1f;

                asteroid1->speed = Vector2(-(*itr)->speed.y, (*itr)->speed.x) * 0.1f;
                asteroid2->speed = Vector2((*itr)->speed.y, -(*itr)->speed.x) * 0.1f;

                Asteroid::Asteroids.push_back(asteroid1);
                Asteroid::Asteroids.push_back(asteroid2);

                // remove o tiro
                delete (*itr);
                itr = shots.erase(itr);

                return true;
            }
            else
            {
                ++itr;
            }
        }
    }

    return false;
}

void Spacecraft::update(int dt)
{
    position += speed;

    if(position.x < 0)
        position.x = Game::WIDTH;
    if(position.y < 0)
        position.y = Game::HEIGHT;
    if(position.x > Game::WIDTH)
        position.x = 0;
    if(position.y > Game::HEIGHT)
        position.y = 0;

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

    // detecta colisoes
    for(AsteroidIter itr = Asteroid::Asteroids.begin(); itr != Asteroid::Asteroids.end();)
    {
        if(!(*itr)->IsDead() && !(*itr)->IsDying())
        {
            if(ShotsCollideWith((*itr)))
            {
                delete (*itr);
                itr = Asteroid::Asteroids.erase(itr);
            }
            else
            {
                ++itr;
            }
        }
        else
        {
            ++itr;
        }
    }

    // 4 segundos de imortabilidade para se recuperar do hit
    if(isHit)
    {
        immortalityTimer -= dt;

        if(immortalityTimer <= 0.f)
        {
            isHit = false;
        }
    }
}

void Spacecraft::GotHit()
{
    isHit = true;
    speed.Zero();
    immortalityTimer = IMMORTALITY_DELAY;
    --lives;
}

bool Spacecraft::IsHit() const
{
    return isHit;
}
