#include "apptodolist.h"
#include "machine.h"
#include "components.h"

void AppTodoList::tick(Machine &machine)
{
  render();
  
  Actions btn = NO_ACTION;
  while(btn == NO_ACTION) {
    btn = (Actions) Button::pollButtons();
  }
  switch(btn) {
    case HOME :
    {
      machine.SetApp(Machine::AppId::HOME);
    }
    break;
    default : 
    {
      
    }
  }
  
}

void AppTodoList::render() const
{
  screenField buttonArea;
  buttonArea.leftEdge = 50;
  buttonArea.topEdge = 50;
  buttonArea.rightEdge = 90;
  buttonArea.bottomEdge = 90;
  Button dbButton(Actions::HOME, red, buttonArea);
  dbButton.display(); // PROBLEM
  //delay(5000);
}
