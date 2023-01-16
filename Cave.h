#ifndef CAVE_H
#define CAVE_H

#include "Polygon.h"

class Cave: public Polygon
{
public:
    Cave(int location);

    void Draw();

    static const int MAX_HEIGHT = 60;
    static const int MIN_HEIGHT = 5;
    static const int MAX_WIDTH = 60;
    static const int MIN_WIDTH = 10;

private:
    float startPoint;
};

#endif // CAVE_H
