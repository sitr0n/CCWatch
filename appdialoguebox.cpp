#include "appdialoguebox.h"
#include "machine.h"
#include "components.h"

void AppDialoguebox::tick(Machine &machine)
{
  render();
  
  Actions btn = NO_ACTION;
  while(btn == NO_ACTION) {
    btn = (Actions) Button::pollButtons();
  }
  switch(btn) {
    case Actions::HOME :
    {
      machine.SetApp(Machine::AppId::HOME);
    }
    break;
    default : 
    {
      
    }
  }
  
}

void AppDialoguebox::render() const
{
  auto position = App::getPosition();
  auto windowArea = position;
  Window wnd("Alert", blue, windowArea);
  wnd.display();
  
  int bodyPadding = 0.63*EDGE_CURVE;
  int buttonHeight = 80;
  int windowWidth = position.rightEdge - position.leftEdge;
  auto leftButtonArea = windowArea;
  leftButtonArea.leftEdge += (bodyPadding + WINDOW_FRAME_WIDTH);
  leftButtonArea.rightEdge = windowWidth/2;
  leftButtonArea.rightEdge -= bodyPadding/2;
  leftButtonArea.bottomEdge -= (bodyPadding + WINDOW_FRAME_WIDTH);
  leftButtonArea.topEdge = leftButtonArea.bottomEdge - buttonHeight;
  Button rejectButton(Actions::NO_ACTION, red, leftButtonArea);
  rejectButton.display();

  auto rightButtonArea = windowArea;
  rightButtonArea.leftEdge = windowWidth/2;
  rightButtonArea.leftEdge += bodyPadding/2;
  rightButtonArea.rightEdge -= (bodyPadding + WINDOW_FRAME_WIDTH);
  rightButtonArea.bottomEdge -= (bodyPadding + WINDOW_FRAME_WIDTH);
  rightButtonArea.topEdge = rightButtonArea.bottomEdge - buttonHeight;
  Button acceptButton(Actions::HOME, green, rightButtonArea);
  acceptButton.display();
  
  auto textArea = windowArea;
  textArea.leftEdge += (bodyPadding + WINDOW_FRAME_WIDTH);
  textArea.topEdge += (bodyPadding + WINDOW_HEADER_HEIGHT);
  textArea.rightEdge -= (bodyPadding + WINDOW_FRAME_WIDTH);
  textArea.bottomEdge -= (bodyPadding + WINDOW_FRAME_WIDTH + buttonHeight);
  auto tfield = Textfield("yadadadada", white, textArea);
  tfield.setTextSize(2);
  tfield.display();
}
