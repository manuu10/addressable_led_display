#include "../Vec2i.cpp"
#include "FastLED.h"
#include "vector"
#include "../direction.cpp"

#ifndef SNAKEH
#define SNAKEH
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
    Vec2i loc()
    {
        return location;
    }

private:
    Vec2i location;
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

    void increaseSize()
    {

        auto last = segments[segments.size() - 1];
        auto secondlast = segments[segments.size() - 2];
        auto diff = last.loc().sub(secondlast.loc());
        segments.push_back(SnakeSegment(last.loc().add(diff)));
    }
    void draw(void (*painter)(int, int, CRGB))
    {
        for (size_t i = segments.size() - 1; i >= 0; i--)
        {
            auto loc = segments[i].loc();
            painter(loc.x, loc.y, CRGB::Blue);
        }
    }

    void changeDirection(Direction d)
    {
        dir = d;
    }

    void reset()
    {
        Snake();
    }

    SnakeSegment head()
    {
        return segments[0];
    }

private:
    std::vector<SnakeSegment> segments;
    Direction dir;
};

#endif