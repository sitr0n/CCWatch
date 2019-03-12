#pragma once
#include "widget.h"
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

class Machine;

class App
{
public:
  App() {};
  virtual ~App();

  static void init();
  static Position2D getPosition() { return _position; };
  
  virtual void tick(Machine &context) = 0;
  //virtual void render() const = 0;
  virtual void render() = 0;

protected:
  static Position2D _position;
};
