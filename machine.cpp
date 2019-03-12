#include "machine.h"
#include "app.h"
#include "apphome.h"

Machine::Machine()
{
  App::init();
  running = true;

  this->app = new AppHome();
}

Machine::~Machine()
{
  delete this->app;
}

void Machine::tick()
{
  (this->app)->tick(*this);
}

void Machine::SetApp(AppId app)
{
  delete this->app;
  switch(app) {
    case AppId::HOME :
      this->app = new AppHome();
    break;
    
  }
}

