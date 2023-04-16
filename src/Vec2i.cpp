#include "direction.cpp"
#ifndef VEC2H
#define VEC2H

class Vec2i
{
public:
    Vec2i() = default;
    Vec2i(int xx, int yy)
    {
        x = xx;
        y = yy;
    }
    Vec2i(Direction dir)
    {
        if (dir == Direction::down)
            Vec2i(0, 1);
        else if (dir == Direction::up)
            Vec2i(0, -1);
        else if (dir == Direction::right)
            Vec2i(1, 0);
        else if (dir == Direction::left)
            Vec2i(-1, 0);

        Vec2i();
    }

    int x;
    int y;
    Vec2i add(Vec2i other)
    {
        return Vec2i(x + other.x, y + other.y);
    }
    Vec2i sub(Vec2i other)
    {
        return Vec2i(x - other.x, y - other.y);
    }
    bool operator==(Vec2i other)
    {
        return x == other.x && y == other.y;
    }
    bool inScreenBounds(int xMax, int yMax)
    {
        return x >= 0 && y >= 0 && y < yMax && x < xMax;
    }
    bool outOfRightEdge(int xMax)
    {
        return x >= xMax;
    }
    bool outOfBottomEdge(int yMax)
    {
        return y >= yMax;
    }
    bool outOfLeftEdge()
    {
        return x < 0;
    }
    bool outOfTopEdge()
    {
        return y < 0;
    }
};

#endif