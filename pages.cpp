#include "pages.h"

void Pages::tick()
{
  bool ok = Button::pollButtons();
}

void Pages::dialogueBox(String title, String text)
{
  auto windowArea = _position;
  Window wnd(title, blue, windowArea);
  wnd.display();
  
  int bodyPadding = 0.63*EDGE_CURVE;
  int buttonHeight = 80;
  int windowWidth = _position.rightEdge - _position.leftEdge;
  auto leftButtonArea = windowArea;
  leftButtonArea.leftEdge += (bodyPadding + WINDOW_FRAME_WIDTH);
  leftButtonArea.rightEdge = windowWidth/2;
  leftButtonArea.rightEdge -= bodyPadding/2;
  leftButtonArea.bottomEdge -= (bodyPadding + WINDOW_FRAME_WIDTH);
  leftButtonArea.topEdge = leftButtonArea.bottomEdge - buttonHeight;
  Button rejectButton(1, red, leftButtonArea);
  rejectButton.display();

  auto rightButtonArea = windowArea;
  rightButtonArea.leftEdge = windowWidth/2;
  rightButtonArea.leftEdge += bodyPadding/2;
  rightButtonArea.rightEdge -= (bodyPadding + WINDOW_FRAME_WIDTH);
  rightButtonArea.bottomEdge -= (bodyPadding + WINDOW_FRAME_WIDTH);
  rightButtonArea.topEdge = rightButtonArea.bottomEdge - buttonHeight;
  Button acceptButton(2, green, rightButtonArea);
  acceptButton.display();
  
  auto textArea = windowArea;
  textArea.leftEdge += (bodyPadding + WINDOW_FRAME_WIDTH);
  textArea.topEdge += (bodyPadding + WINDOW_HEADER_HEIGHT);
  textArea.rightEdge -= (bodyPadding + WINDOW_FRAME_WIDTH);
  textArea.bottomEdge -= (bodyPadding + WINDOW_FRAME_WIDTH + buttonHeight);
  auto tfield = Textfield(text, white, textArea);
  tfield.setTextSize(2);
  tfield.display();
}

