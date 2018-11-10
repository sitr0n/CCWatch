#include "machine.h"
#include "app.h"
#include "apphome.h"
#include "appdialoguebox.h"
#include "apptodolist.h"

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
  app->tick(*this);
}

void Machine::SetApp(AppId app)
{
  delete this->app;
  switch(app) {
    case AppId::HOME :
      this->app = new AppHome();
    break;
      
    case AppId::DIALOGUE_BOX :
      this->app = new AppDialoguebox();
    break;
      
    case AppId::TODO_LIST :
      this->app = new AppTodoList();
    break;
  }
}

