#include "../Vec2i.cpp";
#include <FastLED.h>

#ifndef PADDLEH
#define PADDLEH
class PlayerPaddle
{
public:
    PlayerPaddle() = default;
    PlayerPaddle(Vec2i pos, int s, CRGB col)
    {
        size = s;
        color = col;
        position = pos;
    }

    Vec2i bottom()
    {
        return position.add(Vec2i(0, size));
    }
    Vec2i pos()
    {
        return position;
    }

    void changeVelocity(Vec2i v)
    {
        velocity = v;
    }

    void update(Vec2i boardSize)
    {
        Vec2i newPos = position.add(velocity);
        if (newPos.inScreenBounds(boardSize.x, boardSize.y))
        {
            position = newPos;
        }
    }

    void draw(void (*painter)(int, int, CRGB))
    {
        for (int i = 0; i < size; i++)
        {
            painter(position.x, position.y + i, color);
        }
    }

    void handleInput(String input)
    {
        if (input == "down")
            velocity = Vec2i(0, 1);
        else if (input == "up")
            velocity = Vec2i(0, -1);
        else if (input == "release")
            velocity = Vec2i(0, 0);
    }

private:
    Vec2i position;
    Vec2i velocity;
    CRGB color;
    int size;
};
#endif