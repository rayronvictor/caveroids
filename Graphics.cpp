#include <QtOpenGL/QtOpenGL>
#include <math.h>

#include "Graphics.h"
#include "Math2.h"

void Graphics::SetClearColor(float r, float g, float b, float a)
{
    //Clamp é para garantir que vai ficar entre 0.f e 1.f
    glClearColor(Math::Clamp(r, 0.f, 1.f),
                 Math::Clamp(g, 0.f, 1.f),
                 Math::Clamp(b, 0.f, 1.f),
                 Math::Clamp(a, 0.f, 1.f));
}

void Graphics::SetClearColor(Color& clearColor)
{
    //Clamp é para garantir que vai ficar entre 0.f e 1.f
    glClearColor(Math::Clamp(clearColor.R, 0.f, 1.f),
                 Math::Clamp(clearColor.G, 0.f, 1.f),
                 Math::Clamp(clearColor.B, 0.f, 1.f),
                 Math::Clamp(clearColor.A, 0.f, 1.f));
}

void Graphics::ClearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::SwapBuffers()
{
    SwapBuffers();
}

void Graphics::Set2dMode(int width, int height)
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Graphics::BeginPoints()
{
    glBegin(GL_POINTS);
}

void Graphics::BeginLines()
{
    glBegin(GL_LINES);
}

void Graphics::BeginLineStrip()
{
    glBegin(GL_LINE_STRIP);
}

void Graphics::BeginLineLoop()
{
    glBegin(GL_LINE_LOOP);
}

void Graphics::BeginTriangles()
{
    glBegin(GL_TRIANGLES);
}

void Graphics::BeginTriangleStrip()
{
    glBegin(GL_TRIANGLE_STRIP);
}

void Graphics::BeginTriangleFan()
{
    glBegin(GL_TRIANGLE_FAN);
}

void Graphics::BeginQuads()
{
    glBegin(GL_QUADS);
}

void Graphics::BeginQuadStrip()
{
    glBegin(GL_QUAD_STRIP);
}

void Graphics::BeginPolygons()
{
    glBegin(GL_POLYGON);
}

void Graphics::BeginCircles()
{
    glBegin(GL_LINE_STRIP);
}

void Graphics::End()
{
    glEnd();
}

void Graphics::DrawLine(float x1, float y1, float x2, float y2, Color& color)
{
    glBegin(GL_LINES);
        glColor4f(color.R, color.G, color.B, color.A);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}

void Graphics::DrawRectangle(float x, float y, int w, int h, float angle, const Color& color)
{
    glBegin(GL_QUADS);
        glColor4f(color.R, color.G, color.B, color.A);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}

void Graphics::DrawTriangle(float x, float y, int height, int baseline, float angle, Color& color)
{
    glBegin(GL_TRIANGLES);
        glColor4f(color.R, color.G, color.B, color.A);
        glVertex2f(x, y - height/2);
        glVertex2f(x + baseline/2, y + height/2);
        glVertex2f(x - baseline/2, y + height/2);
    glEnd();
}

void Graphics::DrawCircle(float cx, float cy, float radius, Color& color)
{
    glBegin(GL_LINES);
        glColor4f(color.R, color.G, color.B, color.A);
        for(int i = 0; i < 360; i += 2)
            glVertex2f(cx + radius * cos(i * Math::Degs2Rads), cy + radius * sin(i * Math::Degs2Rads));
    glEnd();
}
