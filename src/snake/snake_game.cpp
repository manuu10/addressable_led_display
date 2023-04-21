#include "../Vec2i.cpp";
#include "./snake.cpp";
#include "./food.cpp";
#include <FastLED.h>

#ifndef SNAKEGH
#define SNAKEGH
class SnakeGame
{
public:
    SnakeGame() = default;
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
    void onPlayerInput(String player, String input)
    {
        if (input == "left")
            snake.changeDirection(Direction::left);
        else if (input == "right")
            snake.changeDirection(Direction::right);
        else if (input == "up")
            snake.changeDirection(Direction::up);
        else if (input == "down")
            snake.changeDirection(Direction::down);
    }

private:
    Vec2i boardSize;
    Snake snake;
    Food food;
};

#endif