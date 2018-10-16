#include "graphics.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void Graphics::Init()
{
  tft.begin();
  tft.fillRect(0, 0, tft.width(), tft.height(), black);
}

void Graphics::fillRect()
{
  int width = _position.rightEdge - _position.leftEdge;
  int height = _position.bottomEdge - _position.topEdge;
  tft.fillRect(_position.leftEdge, _position.topEdge, width, height, _color);
}

void Graphics::fillCircle()
{
  int width = _position.rightEdge - _position.leftEdge;
  int height = _position.bottomEdge - _position.topEdge;
  int radius = (width >= height) ? height/2 : width/2;
  int centerX = _position.leftEdge + width/2;
  int centerY = _position.topEdge + height/2;
  tft.fillCircle(centerX, centerY, radius - 1, _color);
}

void Graphics::Print(String text)
{
  int fieldHeight = _position.bottomEdge - _position.topEdge + 1;
  if (fieldHeight < TEXT_HEIGHT)
    return;
  
  tft.setCursor(_position.leftEdge + 1, _position.topEdge + fieldHeight%TEXT_HEIGHT);
  int textSize = (int)(fieldHeight/TEXT_HEIGHT - (fieldHeight%TEXT_HEIGHT)/10);
  tft.setTextSize(textSize);
  tft.setTextColor(_color);
  
  int fieldWidth = _position.rightEdge - _position.leftEdge;
  int textWidth = text.length()*TEXT_WIDTH*textSize;
  if (textWidth > fieldWidth) {
    int charactersToRemove = (int)((textWidth - fieldWidth)/(TEXT_WIDTH*textSize)) + 1;
    int numberOfFittingCharacters = text.length() - charactersToRemove;

    text.remove(numberOfFittingCharacters - 1);
    text += '~';
  }
  tft.print(text);
}
