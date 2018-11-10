#pragma once
#include "components.h"

class Machine;

class App
{
public:
  App() {};
  virtual ~App();

  static void init();
  static screenField getPosition() { return _position; };
  
  virtual void tick(Machine &context) = 0;
  virtual void render() const = 0;

protected:
  static screenField _position;
};
