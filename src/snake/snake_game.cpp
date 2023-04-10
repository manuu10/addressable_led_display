#include "../Vec2i.cpp";
#include "./snake.cpp";
#include "./food.cpp";
#include <FastLED.h>

class SnakeGame
{
public:
    SnakeGame(Vec2i size)
    {
        boardSize = size;
        snake = Snake();
        food = Food(size.x, size.y);
    }

    void update()
    {
    }

    void draw(CRGB *leds)
    {
    }

private:
    Vec2i boardSize;
    Snake snake;
    Food food;
};