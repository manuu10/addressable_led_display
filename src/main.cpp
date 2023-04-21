#include <FastLED.h>
#include <Vec2i.cpp>
#include <snake/snake_game.cpp>
#include <pong/pong.cpp>
#include <start_screens/start_screens.cpp>
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

enum GameType
{
  snek,
  peng,
};
SnakeGame snakeGame;
PongGame pongGame;
GameType currentGame = GameType::peng;

ESP8266WebServer server(80);
String newHostname = "awesome-led-matrix";

void gameDraw();
void gameUpdate();
void gameDrawIntros();

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
  }

  Serial.print("Connected. IP: ");
  Serial.println(WiFi.localIP());
}

void onDoPlayerInput()
{
  String player = "";
  String input = "";
  for (int i = 0; i < server.args(); i++)
  {
    if (server.argName(i) == "player")
      player = server.arg(i);
    if (server.argName(i) == "input")
      input = server.arg(i);
  }
  snakeGame.onPlayerInput(player, input);
  pongGame.onPlayerInput(player, input);
}

void onSwitchGame()
{
  String game = "";
  for (int i = 0; i < server.args(); i++)
  {
    if (server.argName(i) == "game")
      game = server.arg(i);
  }
  if (game == "snake")
  {
    currentGame = GameType::snek;
  }
  if (game == "pong")
  {
    currentGame = GameType::peng;
  }
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

void setup_routing()
{

  server.on("/doPlayerInput", HTTP_GET, onDoPlayerInput);
  server.on("/switchGame", HTTP_GET, onSwitchGame);
  server.begin();
}

void setup()
{
  Serial.begin(9600);
  snakeGame = SnakeGame(Vec2i(NUM_COLS, NUM_ROWS));
  pongGame = PongGame(Vec2i(NUM_COLS, NUM_ROWS));
  delay(3000); // 3 second delay for recovery
  connect_to_wifi();
  setup_routing();
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.println("setup done");
}

void loop()
{
  server.handleClient();
  gameDraw();
  gameDrawIntros();
  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);
  EVERY_N_MILLISECONDS(100) { gameUpdate(); }
}

void gameDraw()
{
  fadeToBlackBy(leds, NUM_LEDS, 255);
  if (currentGame == GameType::peng)
    pongGame.draw(paintPixelAt);
  if (currentGame == GameType::snek)
    snakeGame.draw(paintPixelAt);
}

void gameUpdate()
{
  if (currentGame == GameType::peng)
    pongGame.update();
  if (currentGame == GameType::snek)
    snakeGame.update();
}

void gameDrawIntros()
{
}
