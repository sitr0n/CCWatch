#pragma once
#include "app.h"

class AppHome : public App
{
  public:
    void tick(Machine &machine);
  protected:
    enum Actions { NO_ACTION = 0, DIALOGUE_BOX, TODO_LIST };
  
    virtual void render() const;
};

