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
        if (!snake.head().loc().inScreenBounds(boardSize.x, boardSize.y))
        {
            reset();
        }
    }

    void draw(void (*painter)(int, int, CRGB))
    {
        snake.draw(painter);
        food.draw(painter);
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

    void reset()
    {
        snake = Snake();
        food.newPosition();
    }

private:
    Vec2i boardSize;
    Snake snake;
    Food food;
};

#endif