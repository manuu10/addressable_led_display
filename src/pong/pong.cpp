#include "../Vec2i.cpp";
#include "paddle.cpp";
#include "ball.cpp";

#include <FastLED.h>

#ifndef PONGGH
#define PONGGH
class PongGame
{
public:
    PongGame() = default;
    PongGame(Vec2i size)
    {
        boardSize = size;

        reset();
    }

    void update()
    {
        leftPlayer.update(boardSize);
        rightPlayer.update(boardSize);
        ball.update(boardSize, {leftPlayer, rightPlayer});
        if (ball.outOfBounds(boardSize))
        {
            delay(2000);
            reset();
        }
    }

    void draw(void (*painter)(int, int, CRGB))
    {
        rightPlayer.draw(painter);
        leftPlayer.draw(painter);
        ball.draw(painter);
    }

    void onPlayerInput(String player, String input)
    {
        if (player == "left")
            leftPlayer.handleInput(input);
        else if (player == "right")
            rightPlayer.handleInput(input);
    }

private:
    void reset()
    {
        leftPlayer = PlayerPaddle(Vec2i(0, 4), 5, CRGB::Red);
        rightPlayer = PlayerPaddle(Vec2i(boardSize.x - 1, 4), 5, CRGB::Blue);
        ball = Ball(Vec2i(0, 0), CRGB::Green);
    }
    PlayerPaddle leftPlayer;
    PlayerPaddle rightPlayer;
    Ball ball;
    Vec2i boardSize;
};
#endif