#include "Game.h"
#include "Asteroid.h"
#include <iostream>

int Game::WIDTH = 900; // largura do jogo
int Game::HEIGHT = 600; // altura do jogo

Game::Game()
{
    keys[Qt::Key_Left] = false;
    keys[Qt::Key_Right] = false;
    keys[Qt::Key_Up] = false;
    keys[Qt::Key_Down] = false;
    keys[Qt::Key_Space] = false;

    explosion = NULL;
    flyingSaucer = NULL;
    this->Load();
}

Game::~Game()
{
    delete spacecraft;
    delete explosion;
    delete caveTop;
    delete caveBottom;
    delete sky;
    delete flyingSaucer;
}

void Game::Load()
{

    spacecraft = new Spacecraft(Game::WIDTH / 2.f, Game::HEIGHT / 2.f);
    caveTop = new Cave(1);
    caveBottom = new Cave(0);
    sky = new Sky();

    flyTimerShow = FLY_TIMER_SHOW;
    flySmart = false;

    for(int i = 0; i < NUMBER_OF_ASTEROIDS; ++i)
    {
        // gera uma posição randômica
        int x = Math::Random(0.f, (float)Game::WIDTH);
        int y = Math::Random(0.f, (float)Game::HEIGHT);

        if(x < 0)
            x = Game::WIDTH / 6.f;
        if(y < 0)
            y = Game::HEIGHT / 8.f;

        // garante que nenhum asteroid vai iniciar no meio
        // 300 <= x <= 450
        if(x >= Game::WIDTH / 3.f && x <= Game::WIDTH / 2.f)
            x = Game::WIDTH / 3.f;
        // 450 <= x <= 600
        else if(x >= Game::WIDTH / 2.f && x <= Game::WIDTH - Game::WIDTH / 3.f)
            x = Game::WIDTH - Game::WIDTH / 3.f;

        // garante que nenhum asteroid vai iniciar no meio
        // 200 <= y <= 300
        if(y >= Game::HEIGHT / 3.f && y <= Game::HEIGHT / 2.f)
            y = Game::HEIGHT / 3.f;
        // 300 <= y <= 400
        else if(y >= Game::HEIGHT / 2.f && y <= Game::HEIGHT - Game::HEIGHT / 3.f)
            y = Game::HEIGHT - Game::HEIGHT / 3.f;

        // adiciona na lista de asteroids do jogo
        Asteroid::Asteroids.push_back(new Asteroid(x, y, Math::Random(0.f, 359.f), INITIAL_SIZE));
    }
}

void Game::Draw()
{
    caveTop->Draw();
    caveBottom->Draw();
    sky->Draw();

    if(flyingSaucer)    flyingSaucer->Draw();

    // desenha os asteroids
    for(AsteroidIter itr = Asteroid::Asteroids.begin(); itr != Asteroid::Asteroids.end(); ++itr)
    {
        if((*itr)) (*itr)->Draw();
    }


    if(explosion)
    {
        explosion->Draw();
    }
    else
    {
        if(spacecraft->lives > 0)   spacecraft->Draw();
    }
}

void Game::update(int dt)
{
    updateSpacecraft(dt);
    updateAsteroids(dt);
    updateExplosion(dt);
    updateSky(dt);
    updateFlyingSaucer(dt);

    flyTimerShow -= dt;
}

void Game::updateSpacecraft(int dt)
{
    if(keys[Qt::Key_Up])
    {
        spacecraft->moveForward(dt);
    }
    else
    {
        if(keys[Qt::Key_Down])
        {
            spacecraft->moveBack(dt);
        }
        else
        {
            spacecraft->decelerate(dt);
        }
    }

    if(keys[Qt::Key_Left])
    {
        spacecraft->Rotate(spacecraft->GetAngle() - Spacecraft::SPINSPEED * dt);
    }
    else if(keys[Qt::Key_Right])
    {
        spacecraft->Rotate(spacecraft->GetAngle() + Spacecraft::SPINSPEED * dt);
    }

    if(keys[Qt::Key_Space] && !spacecraft->IsHit()) spacecraft->FireShot();

    spacecraft->update(dt);

    if(!spacecraft->IsHit())
    {

        // checa colisão com o Disco-voador
        if(flyingSaucer)
        {
            if(spacecraft->CollidesWith(flyingSaucer)){
                // cria uma explosão
                explosion = new Explosion(40, spacecraft->position, 0.2f);
                // opa, foi atingido
                spacecraft->GotHit();
            }
            else
            {
                if(flyingSaucer->shots.size() > 0)
                {
                    if(spacecraft->CollideWithShotsOfFlyingSaucer(flyingSaucer))
                    {
                        // cria uma explosão
                        explosion = new Explosion(40, spacecraft->position, 0.2f);
                        // opa, foi atingido
                        spacecraft->GotHit();
                    }
                }
            }
        }

        // checa colisões com as cavernas
        if(spacecraft->CollidesWith(caveTop) || spacecraft->CollidesWith(caveBottom))
        {
            // cria uma explosão
            explosion = new Explosion(40, spacecraft->position, 0.2f);
            // opa, foi atingido
            spacecraft->GotHit();
        }

        // checa colisões com asteroids
        for(AsteroidIter itr = Asteroid::Asteroids.begin(); itr != Asteroid::Asteroids.end(); ++itr)
        {
            if(spacecraft->CollidesWith(*itr) && !(*itr)->IsDying() && !(*itr)->IsDead())
            {
                // cria uma explosão
                explosion = new Explosion(40, spacecraft->position, 0.2f);

                (*itr)->speed = spacecraft->speed / 50.f;

                // opa, foi atingido
                spacecraft->GotHit();
            }
        }
    }
}

void Game::updateAsteroids(int dt)
{
    for(AsteroidIter itr = Asteroid::Asteroids.begin(); itr != Asteroid::Asteroids.end();)
    {
        // verifica se está morto
        if(!(*itr)->IsDead())
        {
            // se não estiver atualiza ele
            (*itr)->update(dt);
            ++itr;
        }
        else
        {
            // se estiver, infelizmente vai ter que ir embora
            delete (*itr);
            itr = Asteroid::Asteroids.erase(itr);
        }
    }
}

void Game::updateExplosion(int dt)
{
    if(explosion)
    {
        explosion->update(dt);

        if(explosion->dead)
        {
            delete explosion;
            explosion = NULL;

            bool hit = false;

            do
            {
                hit = false;

                // gera aleatoriamente uma nova posição
                spacecraft->position = Vector2(Math::Random(40, Game::WIDTH - 40), Math::Random(0, Game::HEIGHT));

                // verifica se colide com as cavernas
                if(spacecraft->CollidesWith(caveTop) || spacecraft->CollidesWith(caveBottom))
                {
                    hit = true;
                }
                else
                {// ou com algum asteroid
                    for(AsteroidIter itr = Asteroid::Asteroids.begin(); itr != Asteroid::Asteroids.end(); ++itr)
                    {
                        if(spacecraft->CollidesWith((*itr), 40.f) && !(*itr)->IsDying() && !(*itr)->IsDead())
                        {
                            hit = true;
                        }
                    }
                }
            }while(hit);
        }
    }
}

void Game::updateFlyingSaucer(int dt)
{
    if(flyTimerShow < 0 && !flyingSaucer)
    {
        flySmart = !flySmart;
        flyingSaucer = new FlyingSaucer(flySmart);
        flyingSaucer->position = Vector2(0.f, Game::HEIGHT / 2.f);
        flyTimerShow = FLY_TIMER_SHOW;
    }

    if(flyingSaucer)
    {
        flyingSaucer->FireShot(spacecraft);
        flyingSaucer->update(dt);

        if(flyingSaucer->IsDead() || flyingSaucer->position.x > Game::WIDTH)
        {
            delete flyingSaucer;
            flyingSaucer = NULL;
        }
    }
}

void Game::updateSky(int dt)
{
    sky->update(dt);
}

void Game::keyPressed(QKeyEvent * event)
{
    keys[event->key()] = true;
}

void Game::keyReleased(QKeyEvent *event)
{
    keys[event->key()] = false;
}
