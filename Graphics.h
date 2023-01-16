#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Color.h"

class Graphics
{
        public:
            static void SetClearColor(float r = 0.f, float g = 0.f, float b = 0.f, float a = 0.f);
            static void SetClearColor(Color& clearColor);
            static void ClearScreen();
            static void SwapBuffers();

            static void Set2dMode(int width, int height);

            static void BeginPoints();
            static void BeginLines();
            static void BeginLineStrip();
            static void BeginLineLoop();
            static void BeginTriangles();
            static void BeginTriangleStrip();
            static void BeginTriangleFan();
            static void BeginQuads();
            static void BeginQuadStrip();
            static void BeginPolygons();
            static void BeginCircles();
            static void End();

            // Primitivas
            static void DrawLine(float x1, float y1, float x2, float y2, Color& color);
            static void DrawRectangle(float x, float y, int w, int h, float angle, const Color& color);
            static void DrawTriangle(float x, float y, int height, int baseline, float angle, Color& color);
            static void DrawCircle(float cx, float cy, float radius, Color& color);

        private:

};

#endif
