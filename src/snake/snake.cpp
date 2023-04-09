#include "../Vec2i.cpp"
#include "vector"

enum Direction
{
    up,
    down,
    left,
    right
};

class Snake
{
public:
    Snake()
    {
        segments = {
            SnakeSegment(Vec2i(3, 0)),
            SnakeSegment(Vec2i(2, 0)),
            SnakeSegment(Vec2i(1, 0)),
        };
        dir = Direction::right;
    }

    void update()
    {
        for (size_t i = segments.size() - 1; i >= 1; i--)
        {
            segments[i].follow(segments[i - 1]);
        }
        segments[0].moveBy(Vec2i(dir));
    }

    void changeDirection(Direction d)
    {
        dir = d;
    }

private:
    std::vector<SnakeSegment> segments;
    Direction dir;
};

class SnakeSegment
{
public:
    SnakeSegment(Vec2i loc)
    {
        location = loc;
    }
    void follow(SnakeSegment segment)
    {
        location = segment.location;
    }
    void moveBy(Vec2i velocity)
    {
        location = location.add(velocity);
    }

private:
    Vec2i location;
};