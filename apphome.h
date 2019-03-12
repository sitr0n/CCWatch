#pragma once
#include "app.h"

#include "button.h"
#include "textbrowser.h"

class AppHome : public App
{
  public:
    AppHome() { render(); };
    ~AppHome() {};

    virtual void tick(Machine &context);
    virtual void render();

  private:
    Button* btn;
};

