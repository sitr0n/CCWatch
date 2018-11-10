#include "components.h"
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

Touch *touch;

void Components::clearScreen()
{
  screenField position;
  position.leftEdge = 0;
  position.topEdge = 0;
  position.rightEdge = SCREEN_WIDTH;
  position.bottomEdge = SCREEN_HEIGHT;
  Rectangle r(black, position);
  r.display();
}

void Components::window(String title)
{
  auto frameArea = this->_position;
  fillSurface(_color, frameArea);
  
  screenField bodyArea;
  bodyArea.leftEdge = _position.leftEdge + WINDOW_FRAME_WIDTH;
  bodyArea.topEdge = _position.topEdge + WINDOW_HEADER_HEIGHT;
  bodyArea.rightEdge = _position.rightEdge - WINDOW_FRAME_WIDTH;
  bodyArea.bottomEdge = _position.bottomEdge - WINDOW_FRAME_WIDTH;
  fillSurface(black, bodyArea);

  int titleHorizontalPadding = EDGE_CURVE;
  int titleVerticalPadding = WINDOW_FRAME_WIDTH;
  screenField titleArea;
  titleArea.leftEdge = _position.leftEdge + titleHorizontalPadding;
  titleArea.topEdge = _position.topEdge + titleVerticalPadding;
  titleArea.rightEdge = _position.rightEdge - titleHorizontalPadding;
  titleArea.bottomEdge = bodyArea.topEdge - titleVerticalPadding;
  auto titleText = Text(title, black, titleArea);
  titleText.display();
}

void Components::button(int id, String buttonText)
{
  int width = _position.rightEdge - _position.leftEdge;
  int height = _position.bottomEdge - _position.topEdge;
  int buttonSize = (width >= height) ? height : width;
  int minimumButtonSizeForCurvedStyle = 80;
  
  if (buttonSize >= minimumButtonSizeForCurvedStyle) {
    fillSurface(_color, _position);
  } else {
    Rectangle r(_color, _position);
    r.display();
  }
  if (buttonText.length() > 0) {
    auto textArea = _position;
    Text txt(buttonText, white, textArea);
    txt.display();
  }
  new Touch(id, _position);
}

String Components::textField(String text, int textSize)
{
  String msg = text;
  screenField textField = _position;
  textField.bottomEdge = _position.topEdge + TEXT_HEIGHT*textSize + 1;
  do {
    msg = println(msg, _color, textSize, textField);
    textField.topEdge = textField.bottomEdge + 1;
    textField.bottomEdge = textField.topEdge + TEXT_HEIGHT*textSize + 1;;
  } while (msg.length() > 0 && textField.bottomEdge <= _position.bottomEdge);  
  return msg;
}

String Components::println(String text, Colors color, int fontSize, screenField position)
{
  int charsPerLine = (position.rightEdge - position.leftEdge)/(fontSize*TEXT_WIDTH);
  if (text.length() > charsPerLine) {
    int endOfLine = charsPerLine;
    while (text[endOfLine] != ' ') {
      endOfLine--;
      if (endOfLine < 0) {
        endOfLine = charsPerLine;
        break;
      }
    }
    Text line(text.substring(0, endOfLine), color, position);
    line.display();
    return text.substring(endOfLine + 1);
  } else {
    Text line(text, color, position);
    line.display();
    String empty;
    return empty;
  }
}

void Components::fillSurface(Colors color, screenField position)
{
  const int NUM_GFX_OBJECTS = 9;
  Graphics *frame[NUM_GFX_OBJECTS];
  
  screenField topLeftCornerFrame;
  topLeftCornerFrame.leftEdge = position.leftEdge;
  topLeftCornerFrame.topEdge = position.topEdge;
  topLeftCornerFrame.rightEdge = position.leftEdge + 2*EDGE_CURVE;
  topLeftCornerFrame.bottomEdge = position.topEdge + 2*EDGE_CURVE;
  frame[0] = new Circle(color, topLeftCornerFrame);

  screenField topRightCornerFrame;
  topRightCornerFrame.leftEdge = position.rightEdge - 2*EDGE_CURVE;
  topRightCornerFrame.topEdge = position.topEdge;
  topRightCornerFrame.rightEdge = position.rightEdge;
  topRightCornerFrame.bottomEdge = position.topEdge + 2*EDGE_CURVE;
  frame[1] = new Circle(color, topRightCornerFrame);

  screenField bottomLeftCornerFrame;
  bottomLeftCornerFrame.leftEdge = position.leftEdge;
  bottomLeftCornerFrame.topEdge = position.bottomEdge - 2*EDGE_CURVE;
  bottomLeftCornerFrame.rightEdge = position.leftEdge + 2*EDGE_CURVE;
  bottomLeftCornerFrame.bottomEdge = position.bottomEdge;
  frame[2] = new Circle(color, bottomLeftCornerFrame);

  screenField bottomRightCornerFrame;
  bottomRightCornerFrame.leftEdge = position.rightEdge - 2*EDGE_CURVE;
  bottomRightCornerFrame.topEdge = position.bottomEdge - 2*EDGE_CURVE;
  bottomRightCornerFrame.rightEdge = position.rightEdge;
  bottomRightCornerFrame.bottomEdge = position.bottomEdge;
  frame[3] = new Circle(color, bottomRightCornerFrame);

  screenField leftFrame;
  leftFrame.leftEdge = position.leftEdge;
  leftFrame.topEdge = position.topEdge + EDGE_CURVE;
  leftFrame.rightEdge = position.leftEdge + 2*EDGE_CURVE;
  leftFrame.bottomEdge = position.bottomEdge - EDGE_CURVE;
  frame[4] = new Rectangle(color, leftFrame);

  screenField topFrame;
  topFrame.leftEdge = position.leftEdge + EDGE_CURVE;
  topFrame.topEdge = position.topEdge;
  topFrame.rightEdge = position.rightEdge - EDGE_CURVE;
  topFrame.bottomEdge = position.topEdge + 2*EDGE_CURVE;
  frame[5] = new Rectangle(color, topFrame);

  screenField rightFrame;
  rightFrame.leftEdge = position.rightEdge - 2*EDGE_CURVE;
  rightFrame.topEdge = position.topEdge + EDGE_CURVE;
  rightFrame.rightEdge = position.rightEdge;
  rightFrame.bottomEdge = position.bottomEdge - EDGE_CURVE;
  frame[6] = new Rectangle(color, rightFrame);

  screenField bottomFrame;
  bottomFrame.leftEdge = position.leftEdge + EDGE_CURVE;
  bottomFrame.topEdge = position.bottomEdge - 2*EDGE_CURVE;
  bottomFrame.rightEdge = position.rightEdge - EDGE_CURVE;
  bottomFrame.bottomEdge = position.bottomEdge;
  frame[7] = new Rectangle(color, bottomFrame);

  screenField centerFrame;
  centerFrame.leftEdge = position.leftEdge + 2*EDGE_CURVE ;
  centerFrame.topEdge = position.topEdge + 2*EDGE_CURVE;
  centerFrame.rightEdge = position.rightEdge - 2*EDGE_CURVE;
  centerFrame.bottomEdge = position.bottomEdge - 2*EDGE_CURVE;
  frame[8] = new Rectangle(color, centerFrame);
  
  for (int i = NUM_GFX_OBJECTS - 1; i >= 0; --i) {
    frame[i]->display();
    delete frame[i];
  }
}

ButtonID Button::pollButtons()
{
  ButtonID button = Touch::tick();
  return button;
}
