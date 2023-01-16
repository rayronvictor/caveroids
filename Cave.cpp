#include "Cave.h"
#include "Game.h"

Cave::Cave(int location)
{
    // location é lugar onde ficará a caverna pode ser 0 - em baixo, 1 - em cima

    color = Color::White;

    // define o ponto inicial dependendo do local (em baixo ou em cima)
    if(location)
    {
        startPoint = Math::Random(MIN_HEIGHT, MAX_HEIGHT);
    }
    else
    {
        startPoint = Game::HEIGHT - Math::Random(MIN_HEIGHT, MAX_HEIGHT);
    }

    Vector2 p(0.f, startPoint);

    AddVertex(p);

    // enquanto o ponto em x gerado ainda não é a largura
    while(p.x != Game::WIDTH)
    {
        // nova posição x a partir da anterior
        p.x = p.x + Math::Random(MIN_WIDTH, MAX_WIDTH);

        // nova posição y dependendo do local (em baixo ou em cima)
        if(location)
        {
            p.y = Math::Random(MIN_HEIGHT, MAX_HEIGHT);
        }
        else
        {
            p.y = Game::HEIGHT - Math::Random(MIN_HEIGHT, MAX_HEIGHT);
        }

        // garante o ponto final na mesma altura que inicial
        if(p.x > Game::WIDTH)
        {
            p.x = Game::WIDTH;
            p.y = startPoint;
        }

        AddVertex(p);
    }

    // fecha o desenho da caverna dependendo do local (em baixo ou em cima)
    if(location)
    {
        AddVertex(Vector2(Game::WIDTH, 0.f));
        AddVertex(Vector2(0.f, 0.f));
    }
    else
    {
        AddVertex(Vector2(Game::WIDTH, Game::HEIGHT));
        AddVertex(Vector2(0.f, Game::HEIGHT));
    }

    AddVertex(Vector2(0.f, startPoint));

}

void Cave::Draw()
{
    glLoadIdentity();

    for(unsigned int i = 1; i < vertices.size(); ++i)
        Graphics::DrawLine(vertices[i-1].x, vertices[i-1].y, vertices[i].x, vertices[i].y, color);
}
