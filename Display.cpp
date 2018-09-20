#include "Display.h"

static Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


Display::Display(Colors color, screenField position) :
  _color(color),
  _position(position),
  _edgeCurve(0)
{

}

void Display::Init()
{
  tft.begin();
  tft.fillRect(0, 0, tft.width(), tft.height(), black);
}

void Display::setEdgeCurves(double rate)
{
  curveRate value = rate;
  if (value > 1) {
    value = 1;
  }
  if (value < 0) {
    value = 0;
  }
  _edgeCurve = (curveRate) value;
}

void Display::draw()
{
  int areaWidth = _position.rightEdge - _position.leftEdge;
  int areaHeight = _position.bottomEdge - _position.topEdge + 1;

  
  if (_edgeCurve == 0) {
    tft.fillRect(_position.leftEdge, _position.topEdge, areaWidth, areaHeight, _color);
  } else {
    int cornerBoxSize;
    if (areaWidth > areaHeight) {
      cornerBoxSize = (int)(_edgeCurve*areaHeight/2);
    } else {
      cornerBoxSize = (int)(_edgeCurve*areaWidth/2);
    }
    //Draw top frame
    tft.fillRect(_position.leftEdge + cornerBoxSize, _position.topEdge + 1, areaWidth - 2*cornerBoxSize, cornerBoxSize, _color);
    //Draw bottom frame
    tft.fillRect(_position.leftEdge + cornerBoxSize, _position.bottomEdge - cornerBoxSize + 1, areaWidth - 2*cornerBoxSize, cornerBoxSize, _color);
    //Draw left frame
    tft.fillRect(_position.leftEdge + 1, _position.topEdge + cornerBoxSize, cornerBoxSize, areaHeight -  2*cornerBoxSize, _color);
    //Draw right frame
    tft.fillRect(_position.rightEdge - cornerBoxSize, _position.topEdge + cornerBoxSize, cornerBoxSize, areaHeight -  2*cornerBoxSize, _color);
    //Draw center
    tft.fillRect(_position.leftEdge + cornerBoxSize, _position.topEdge + cornerBoxSize, areaWidth - 2*cornerBoxSize, areaHeight -  2*cornerBoxSize, _color);
    for (int y = 0; y < cornerBoxSize; y++) {
      for (int x = 0; x < cornerBoxSize; x++) {
        if (pointWithinCircle(x, y, cornerBoxSize)) {
          //Draw top left corner
          tft.drawPixel(_position.leftEdge + cornerBoxSize - x, _position.topEdge + cornerBoxSize - y, _color);
          //Draw top right corner
          tft.drawPixel(_position.leftEdge + areaWidth - (cornerBoxSize - x), _position.topEdge + cornerBoxSize - y, _color);
          //Draw bottom left corner
          tft.drawPixel(_position.leftEdge + cornerBoxSize - x, _position.topEdge + areaHeight - (cornerBoxSize - y), _color);
          //Draw bottom right corner
          tft.drawPixel(_position.leftEdge + areaWidth - (cornerBoxSize - x), _position.topEdge + areaHeight - (cornerBoxSize - y), _color);
        }
      }
    }
  }
}

bool Display::pointWithinCircle(int x, int y, int radius)
{
  bool test = x*x + y*y <= radius*radius;
  return test;
}

void Display::Print(String text, Colors color, screenField position)
{
  int fieldHeight = position.bottomEdge - position.topEdge + 1;
  if (fieldHeight < TEXT_HEIGHT)
    return;
  
  tft.setCursor(position.leftEdge + 1, position.topEdge + fieldHeight%TEXT_HEIGHT);
  int textSize = (int)(fieldHeight/TEXT_HEIGHT - (fieldHeight%TEXT_HEIGHT)/10);
  tft.setTextSize(textSize);
  tft.setTextColor(color);
  
  int fieldWidth = position.rightEdge - position.leftEdge;
  int textWidth = text.length()*TEXT_WIDTH*textSize;
  if (textWidth > fieldWidth) {
    int charactersToRemove = (int)((textWidth - fieldWidth)/(TEXT_WIDTH*textSize)) + 1;
    int numberOfFittingCharacters = text.length() - charactersToRemove;

    text.remove(numberOfFittingCharacters - 1);
    text += '~';
  }
  tft.print(text);
}

String Display::PrintSection(String message, int textSize, Colors color)
{
  String msg = message;
  screenField textField = _position;
  textField.bottomEdge = _position.topEdge + TEXT_HEIGHT*textSize + 1;
  do {
    msg = PrintOneLine(msg, color, textField);
    textField.topEdge = textField.bottomEdge + 1;
    textField.bottomEdge = textField.topEdge + TEXT_HEIGHT*textSize + 1;;
  } while (msg.length() > 0 && textField.bottomEdge <= _position.bottomEdge);  
  return msg;
}

String Display::PrintOneLine(String message, Colors color, screenField position)
{
  int textSize = 2;
  int charsPerLine = (position.rightEdge - position.leftEdge)/(textSize*TEXT_WIDTH);
  if (message.length() > charsPerLine) {
    int endOfLine = charsPerLine;
    while (message[endOfLine] != ' ') {
      endOfLine--;
      if (endOfLine < 0) {
        endOfLine = charsPerLine;
        break;
      }
    }
    Print(message.substring(0, endOfLine), color, position);
    return message.substring(endOfLine + 1);
  } else {
    Print(message, color, position);
    String empty;
    return empty;
  }
}
