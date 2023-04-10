#include <FastLED.h>
#include <Vec2i.cpp>
#include <app_config.cpp>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

FASTLED_USING_NAMESPACE

#define DATA_PIN 14
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_ROWS 16
#define NUM_COLS 24
#define NUM_LEDS 384
CRGB leds[NUM_LEDS];

#define BRIGHTNESS 96
#define FRAMES_PER_SECOND 120

const char *SSID = AppConfig::WIFI_SSID;
const char *PWD = AppConfig::WIFI_PW;

ESP8266WebServer server(80);
String newHostname = "awesome-led-matrix";

class PlayerPaddle
{
public:
  Vec2i position;
  Vec2i velocity;
  int size;

  Vec2i bottom()
  {
    return position.add(Vec2i(0, size));
  }

  void update()
  {
    Vec2i newPos = position.add(velocity);
    if (newPos.inScreenBounds(NUM_COLS, NUM_ROWS))
    {
      position = newPos;
    }
  }
};

Vec2i ballPosition;
Vec2i ballVelocity;

PlayerPaddle paddleLeft;
PlayerPaddle paddleRight;

void gameDraw();
void gameUpdate();

void resetGame()
{
  ballPosition = Vec2i(0, 0);
  ballVelocity = Vec2i(1, 1);
  paddleRight = {
    position : Vec2i(NUM_LEDS - 1, 10),
    velocity : Vec2i(0, 0),
    size : 6,
  };
  paddleLeft = {
    position : Vec2i(0, 10),
    velocity : Vec2i(0, 0),
    size : 6,
  };
}

void connect_to_wifi()
{
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.mode(WIFI_STA);

  WiFi.hostname(newHostname.c_str());

  WiFi.begin(SSID, PWD);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
    // we can even make the ESP32 to sleep
  }

  Serial.print("Connected. IP: ");
  Serial.println(WiFi.localIP());
}

void setup_routing()
{
  server.on(
      "/playerLeft/up", []()
      { paddleLeft.velocity = {
        Vec2i(0, -1),
        }; 
        server.send(200, "text/plain", "success"); });
  server.on(
      "/playerLeft/release", []()
      { paddleLeft.velocity = {
        Vec2i(0,0 ),
        }; 
        server.send(200, "text/plain", "success"); });
  server.on(
      "/playerLeft/down", []()
      { paddleLeft.velocity = {
        Vec2i(0,1 ),
        }; 
        server.send(200, "text/plain", "success"); });
  server.on(
      "/playerRight/up", []()
      { paddleRight.velocity = {
        Vec2i(0, -1),
        }; 
        server.send(200, "text/plain", "success"); });
  server.on(
      "/playerRight/release", []()
      { paddleRight.velocity = {
        Vec2i(0,0),
        };
        server.send(200, "text/plain", "success"); });
  server.on(
      "/playerRight/down", []()
      { paddleRight.velocity = {
        Vec2i(0,1 ),
        };
        server.send(200, "text/plain", "success"); });
  server.begin();
}

void setup()
{
  resetGame();
  delay(3000); // 3 second delay for recovery
  connect_to_wifi();
  setup_routing();
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop()
{
  server.handleClient();
  gameDraw();
  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);
  EVERY_N_MILLISECONDS(100) { gameUpdate(); } // slowly cycle the "base color" through the rainbow
}

void paintPixelAt(int x, int y, CRGB color)
{
  if (y % 2 != 0)
  {
    x = (NUM_COLS - 1) - x;
  }

  int oneDindex = (y * NUM_COLS) + x; // Indexes
  if (oneDindex >= 0 && oneDindex < NUM_LEDS)
  {
    leds[oneDindex] = color;
  }
}

void gameDraw()
{
  fadeToBlackBy(leds, NUM_LEDS, 255);
  paintPixelAt(ballPosition.x, ballPosition.y, CRGB::Green);
  for (int i = 0; i < paddleLeft.size; i++)
  {
    paintPixelAt(paddleLeft.position.x, paddleLeft.position.y + i, CRGB::Red);
  }
  for (int i = 0; i < paddleRight.size; i++)
  {
    paintPixelAt(paddleRight.position.x, paddleRight.position.y + i, CRGB::Blue);
  }
}

void gameUpdate()
{
  ballPosition = ballPosition.add(ballVelocity);
  if (ballPosition.outOfBottomEdge(NUM_ROWS) || ballPosition.outOfTopEdge())
  {
    ballVelocity.y *= -1;
  }
  if (ballPosition.outOfRightEdge(NUM_COLS) || ballPosition.outOfLeftEdge())
  {
    resetGame();
    delay(2000);
    return;
  }

  paddleLeft.update();
  paddleRight.update();

  if (
      (ballPosition.x == paddleLeft.position.x && ballPosition.y >= paddleLeft.position.y && ballPosition.y <= paddleLeft.bottom().y) ||
      (ballPosition.x == paddleRight.position.x && ballPosition.y >= paddleRight.position.y && ballPosition.y <= paddleRight.bottom().y))
  {
    ballVelocity.x *= -1;
  }
}
