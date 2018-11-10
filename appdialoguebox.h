#pragma once
#include "app.h"

class AppDialoguebox : public App
{
  public:
    void tick(Machine &machine);
  protected:
    enum Actions { NO_ACTION = 0, HOME };
  
    virtual void render() const;
};

