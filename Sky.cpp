#include "Sky.h"
#include "Game.h"

Sky::Sky()
{
    flashTime = FLASH_TIME;
    color = Color::White;

    // adicionar as estrelas
    for(unsigned int i = 0; i < NUMBER_OF_STARS; ++i)
    {
        AddVertex(Vector2(Math::Random(0, Game::WIDTH), Math::Random(0, Game::HEIGHT)));
    }
}

void Sky::Draw()
{
    glLoadIdentity();

    Graphics::BeginPoints();
        for(unsigned int i = 0; i < vertices.size(); ++i)
        {
            glLineWidth(Math::Random(MIN_STAR_SIZE, MAX_STAR_SIZE));
            glVertex2f(vertices[i].x, vertices[i].y);
        }
    Graphics::End();
}

void Sky::update(int dt)
{
    flashTime -= dt;

    if(flashTime < 0)
    {
        flashTime = FLASH_TIME;

        // altera a posição de uma estrela aleatoriamente
        int rnd = Math::Random(0, NUMBER_OF_STARS - 1);
        vertices[rnd].x = Math::Random(0, Game::WIDTH);
        vertices[rnd].y = Math::Random(0, Game::HEIGHT);
    }
}
