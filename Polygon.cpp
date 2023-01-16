#include "Polygon.h"
#include "Graphics.h"
#include <QtOpenGL/QtOpenGL>

#include <iostream>

Polygon::Polygon()
{
    position.Zero();
    vertices.clear();
    angle = 0.f;
    area = 0.f;
    color = Color::White;
}

Polygon::Polygon(float x, float y)
{
    position.x = x;
    position.y = y;
    vertices.clear();
    angle = 0.f;
    area = 0.f;
    color = Color::White;
}

Polygon::~Polygon()
{
    vertices.clear();
}

void Polygon::Draw()
{
    // uma desenhar padrão

    if(vertices.size() < 3)
            return;

    glLoadIdentity();

    glTranslatef(position.x, position.y, 0);
    glRotatef(-angle, 0, 0, 1.f);
    glTranslatef(-position.x, -position.y, 0);

    Graphics::BeginTriangleFan();
        glColor4f(color.R, color.G, color.B, color.A);

        for(unsigned int i = 0; i < vertices.size(); ++i)
            glVertex2f(vertices[i].x, vertices[i].y);
    Graphics::End();
}

void Polygon::AddVertex(Vector2 vertex)
{
    vertices.push_back(vertex);

    // se tiver mais de 2 vértices dá pra calcular a área e pegar o centro
    if(vertices.size() > 2)
    {
        area = CalculateArea();
        position = GetCenter();
    }
}

void Polygon::Rotate(float angle)
{
    // para não trabalhar com inteiros muito grande
    if(angle < 0.f)
        angle += 360.f;
    else if(angle > 360.f)
        angle -= 360.f;

    this->angle = angle;
}

void Polygon::SetColor(Color& color)
{
    this->color = color;
}

bool Polygon::PointInPolygon(const Vector2& point)
{
    return PointInPolygon(point.x, point.y);
}

bool Polygon::PointInPolygon(float x, float y)
{
    // nem tem como verificar
    if(vertices.size() < 3)
        return false;

    bool inside = false;    // dentro?
    int ni = 0;             // próximo índice

    for(unsigned int i = 0; i < vertices.size(); ++i)
    {
        // pega o próximo índice.
        // pode voltar para o primeiro ponto
        ni = (i + 1 == vertices.size() ? 0 : i + 1);

        // se x estiver entre o vértice atual e o próximo
        if((x >= vertices[i].x && x < vertices[ni].x) || (x >= vertices[ni].x && x < vertices[i].x))
        {
            float difY = vertices[ni].y - vertices[i].y;
            float difX = vertices[ni].x - vertices[i].x;

            if( y <= (difY / difX * (x - vertices[i].x) + vertices[i].y) )
            {
                inside = !inside; // se tá dentro, está fora. se tá fora está dentro rsrs
            }
        }
    }

    return inside;
}

Vector2 Polygon::GetCenter()
{
    Vector2 vector;
    float accx = 0.f;
    float accy = 0.f;
    int ni = 0;         // próximo índice

    for(unsigned int i = 0; i < vertices.size(); ++i)
    {
        // pega o próximo índice.
        // pode voltar para o primeiro ponto
        ni = (i + 1 == vertices.size() ? 0 : i + 1);

        accx += (vertices[i].x + vertices[ni].x) * (vertices[i].x * vertices[ni].y - vertices[ni].x * vertices[i].y);
    }

    for(unsigned int i = 0; i < vertices.size(); ++i)
    {
        // pega o próximo índice.
        // pode voltar para o primeiro ponto
        ni = (i + 1 == vertices.size() ? 0 : i + 1);

        accy += (vertices[i].y + vertices[ni].y) * (vertices[i].x * vertices[ni].y - vertices[ni].x * vertices[i].y);
    }

    vector.x = 1.f/(6.f * area) * accx;
    vector.y = 1.f/(6.f * area) * accy;

    return vector;
}

float Polygon::GetArea()
{
    return area;
}

float Polygon::CalculateArea()
{
    float acc = 0.f;
    int ni = 0;

    for(unsigned int i = 0; i < vertices.size(); ++i)
    {
        // pega o próximo índice.
        // pode voltar para o primeiro ponto
        ni = (i + 1 == vertices.size() ? 0 : i + 1);

        acc += (vertices[i].x * vertices[ni].y - vertices[ni].x * vertices[i].y);
    }

    return abs(0.5f * acc);
}

float Polygon::GetAngle() const
{
    return angle;
}
