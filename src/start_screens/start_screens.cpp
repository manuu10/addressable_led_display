#include <FastLED.h>

class StartScreens
{
public:
    static void playPongIntro(void (*painter)(int, int, CRGB))
    {
        for (int i = 0; i < 9; i++)
        {
            painter(1, 1 + i, CRGB::Red);
        }
        for (int i = 0; i < 5; i++)
        {
            painter(4, 1 + i, CRGB::Red);
            painter(7, 1 + i, CRGB::Red);
            painter(10, 1 + i, CRGB::Red);
            painter(13, 1 + i, CRGB::Red);
            painter(15, 1 + i, CRGB::Red);
            painter(17, 1 + i, CRGB::Red);
            painter(19, 1 + i, CRGB::Red);
        }

        painter(2, 1, CRGB::Red);
        painter(3, 1, CRGB::Red);
        painter(8, 1, CRGB::Red);
        painter(9, 1, CRGB::Red);

        painter(2, 5, CRGB::Red);
        painter(3, 5, CRGB::Red);
        painter(8, 5, CRGB::Red);
        painter(9, 5, CRGB::Red);

        painter(14, 1, CRGB::Red);
        painter(16, 5, CRGB::Red);

        painter(20, 1, CRGB::Red);
        painter(20, 5, CRGB::Red);
        painter(21, 1, CRGB::Red);
        painter(21, 5, CRGB::Red);
        painter(21, 3, CRGB::Red);
        painter(22, 1, CRGB::Red);
        painter(22, 5, CRGB::Red);
        painter(22, 5, CRGB::Red);
        painter(22, 4, CRGB::Red);
        painter(22, 3, CRGB::Red);
    }
};