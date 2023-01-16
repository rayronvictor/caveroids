#ifndef POLYGON_H
#define POLYGON_H

#include "Vector2.h"
#include "Graphics.h"
#include "Color.h"
#include <vector>
#include <QtOpenGL/QtOpenGL>
using namespace std;

class Polygon
{
        public:
            Polygon();
            Polygon(float x, float y);
            ~Polygon(); // para deletar os vértices

            virtual void Draw();
            void AddVertex(Vector2 vertex);
            void Rotate(float angle);
            void SetColor(Color& color);
            bool PointInPolygon(const Vector2& point);
            bool PointInPolygon(float x, float y);

            Vector2 GetCenter();
            float GetArea();
            float GetAngle() const;

            Vector2 position;
            vector<Vector2> vertices;

        protected:
            float angle;
            float area;
            Color color;

            float CalculateArea(); // calcula sempre que adiciona mais uma vértice
};

#endif
