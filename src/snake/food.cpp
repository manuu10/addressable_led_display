#include "../Vec2i.cpp";
#include <random>
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
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> distX(0, rangeX);
        std::uniform_int_distribution<std::mt19937::result_type> distY(0, rangeY);
        Food(Vec2i(distX(rng), distY(rng)));
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