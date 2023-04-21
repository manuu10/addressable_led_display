#include "../Vec2i.cpp";
#include "paddle.cpp";
#include <FastLED.h>

#ifndef BALLH
#define BALLH
class Ball
{
public:
    Ball() = default;
    Ball(Vec2i pos, CRGB col)
    {
        position = pos;
        color = col;
        velocity = Vec2i(1, 1);
    }

    void changeVelocity(Vec2i v)
    {
        velocity = v;
    }

    void update(Vec2i boardSize, std::vector<PlayerPaddle> otherPaddles)
    {
        position = position.add(velocity);
        if (position.outOfBottomEdge(boardSize.y) || position.outOfTopEdge())
        {
            velocity.y *= -1;
        }
        for (size_t i = 0; i < otherPaddles.size(); i++)
        {
            auto paddle = otherPaddles[i];
            if (position.x == paddle.pos().x && position.y >= paddle.pos().y && position.y < paddle.bottom().y)
            {
                velocity.x *= -1;
                break;
            }
        }
    }

    void draw(void (*painter)(int, int, CRGB))
    {
        painter(position.x, position.y, color);
    }

    bool outOfBounds(Vec2i boardSize)
    {
        return position.outOfRightEdge(boardSize.x) || position.outOfLeftEdge();
    }

private:
    Vec2i position;
    Vec2i velocity;
    CRGB color;
};
#endif