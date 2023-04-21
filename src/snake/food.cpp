#include "../Vec2i.cpp"
#include <FastLED.h>
#ifndef FOODH
#define FOODH
class Food
{
public:
    Food() = default;
    Food(int maxX, int maxY)
    {
        rangeX = maxX;
        rangeY = maxY;
        newPosition();
    }
    Food(Vec2i loc)
    {
        location = loc;
    }

    Vec2i loc()
    {
        return location;
    }

    void newPosition()
    {
        location = Vec2i(random(0, rangeX), random(0, rangeY));
    }
    void draw(void (*painter)(int, int, CRGB))
    {
        painter(location.x, location.y, CRGB::Green);
    }

private:
    Vec2i location;
    int rangeX;
    int rangeY;
};
#endif