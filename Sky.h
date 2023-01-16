#ifndef SKY_H
#define SKY_H

#include "Polygon.h"

const int NUMBER_OF_STARS = 100;
const int MAX_STAR_SIZE = 5;
const int MIN_STAR_SIZE = 1;
const int FLASH_TIME = 500.f;

class Sky: public Polygon
{
public:
    Sky();

    void Draw();
    void update(int dt);

private:
    float flashTime;
};

#endif // SKY_H
