#include "app.h"
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

screenField App::_position;
void App::init()
{
  Components::init(SCREEN_WIDTH, SCREEN_HEIGHT);
  _position.leftEdge = 0;
  _position.topEdge = 0;
  _position.rightEdge = SCREEN_WIDTH;
  _position.bottomEdge = SCREEN_HEIGHT;
}

App::~App()
{
  Components::clearScreen();
  Components::clearAllButtons();
}
