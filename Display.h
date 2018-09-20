#pragma once

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CS   15
#define TFT_DC   33
#define SD_CS    14

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define TEXT_WIDTH 6
#define TEXT_HEIGHT 7

enum Colors {
  black = 0x0000,
  white = 0xFFFF,
  blue = 0x001F,
  red = 0xF800,
  green = 0x07E0
};

typedef int Coordinate;
struct screenField {
  Coordinate leftEdge;
  Coordinate topEdge;
  Coordinate rightEdge;
  Coordinate bottomEdge;
};

typedef double curveRate;
struct gfxObject {
  screenField position;
  Colors color;
  curveRate edgeCurve;
  gfxObject *childObject = NULL;
};

class Display {
    public:
        Display(Colors color, screenField position);
        static void Init();

        void Print(String text, Colors color, screenField position);
        String PrintSection(String message, int textSize, Colors color);
        String PrintOneLine(String message, Colors color, screenField position);
        void draw();
        void setEdgeCurves(double rate);
        
    private:
        bool pointWithinCircle(int x, int y, int radius);
        
        screenField _position;
        Colors _color;
        curveRate _edgeCurve;
};
