#include "apphome.h"
#include "machine.h"
#include "components.h"

void AppHome::tick(Machine &machine)
{
  render();
  
  Actions btn = NO_ACTION;
  while(btn == NO_ACTION) {
    btn = (Actions) Button::pollButtons();
  }
  switch(btn) {
    case DIALOGUE_BOX :
    {
      machine.SetApp(Machine::AppId::DIALOGUE_BOX);
    }
    break;
    case TODO_LIST :
    {
      machine.SetApp(Machine::AppId::TODO_LIST);
    }
    break;
    default : 
    {
      
    }
  }
  
}

void AppHome::render() const
{
  screenField dbArea;
  dbArea.leftEdge = 50;
  dbArea.topEdge = 50;
  dbArea.rightEdge = 90;
  dbArea.bottomEdge = 90;
  Button dbButton(Actions::DIALOGUE_BOX, green, dbArea);
  dbButton.display();

  screenField tdlistArea;
  tdlistArea.leftEdge = 120;
  tdlistArea.topEdge = 50;
  tdlistArea.rightEdge = 160;
  tdlistArea.bottomEdge = 90;
  Button tdlistButton(Actions::TODO_LIST, blue, tdlistArea);
  tdlistButton.display();
}

