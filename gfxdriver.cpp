#include "gfxdriver.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#define TFT_CS   15
#define TFT_DC   33
#define SD_CS    14 // ???

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

GFXdriver::GFXdriver()
{
  tft.begin();
  tft.fillRect(0, 0, tft.width(), tft.height(), black);
}

void GFXdriver::fill_rect(Color color, Position2D position)
{
  int width = position.getWidth();
  int height = position.getHeight();
  tft.fillRect(position.leftEdge, position.topEdge, width, height, color);
}

void GFXdriver::fill_circle(Color color, Position2D position)
{
  int radius = position.getShortestSide()/2 -1;
  tft.fillCircle(position.getCenterX(), position.getCenterY(), radius, color);
}

void GFXdriver::print(String text, Color color, Position2D position)
{
  int fieldHeight = position.getHeight() + 1;
  if (fieldHeight < TEXT_HEIGHT)
    return;
  
  tft.setCursor(position.leftEdge + 1, position.topEdge + fieldHeight%TEXT_HEIGHT);
  int textSize = (int)(fieldHeight/TEXT_HEIGHT - (fieldHeight%TEXT_HEIGHT)/10);
  tft.setTextSize(textSize);
  tft.setTextColor(color);
  
  int fieldWidth = position.getWidth();
  int textWidth = text.length()*TEXT_WIDTH*textSize;
  if (textWidth > fieldWidth) {
    int charactersToRemove = (int)((textWidth - fieldWidth)/(TEXT_WIDTH*textSize)) + 1;
    int numberOfFittingCharacters = text.length() - charactersToRemove;

    text.remove(numberOfFittingCharacters - 1);
    text += '~';
  }
  tft.print(text);
}

