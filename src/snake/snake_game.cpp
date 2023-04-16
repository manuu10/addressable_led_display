#include "../Vec2i.cpp";
#include "./snake.cpp";
#include "./food.cpp";
#include <FastLED.h>

#ifndef SNAKEGH
#define SNAKEGH
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
        snake.update();
        if (snake.head().loc() == food.loc())
        {
            snake.increaseSize();
            food.newPosition();
        }
    }

    void draw(void (*painter)(int, int, CRGB))
    {
        snake.draw(painter);
    }

private:
    Vec2i boardSize;
    Snake snake;
    Food food;
};

#endif