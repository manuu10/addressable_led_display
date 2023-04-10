#include "../Vec2i.cpp";
#include <random>

class Food
{
public:
    Food() = default;
    Food(int maxX, int maxY)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> distX(0, maxX);
        std::uniform_int_distribution<std::mt19937::result_type> distY(0, maxY);

        Food(Vec2i(distX(rng), distY(rng)));
    }
    Food(Vec2i loc)
    {
        location = loc;
    }

private:
    Vec2i location;
};