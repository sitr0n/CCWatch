#include "app.h"
#include "gfxdriver.h"
#include "touchscreendriver.h"


Position2D App::_position;
void App::init()
{
  Widget::inject_graphics(new GFXdriver());
  Widget::inject_input(new TouchscreenDriver());
  
  
  
  _position.leftEdge = 0;
  _position.topEdge = 0;
  _position.rightEdge = SCREEN_WIDTH;
  _position.bottomEdge = SCREEN_HEIGHT;
}

App::~App()
{
  //Widget::clearAllButtons();
}
