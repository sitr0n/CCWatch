#pragma once

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_STMPE610.h>

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 3800
#define TS_MAXX 100
#define TS_MINY 100
#define TS_MAXY 3750

#define STMPE_CS 32

typedef int ScreenObject;
typedef int Coordinate;

struct sensitiveScreenField {
  ScreenObject id;
  Coordinate leftEdge;
  Coordinate topEdge;
  Coordinate rightEdge;
  Coordinate bottomEdge;
  sensitiveScreenField *next = NULL;
};

class TouchInput {
    public:
        TouchInput(Coordinate screenWidth, Coordinate screenHeight);
        void addButton(Coordinate leftEdge, Coordinate topEdge, Coordinate rightEdge, Coordinate bottomEdge, ScreenObject id);
        void clearButtons(void); // Not implemented yet.
        ScreenObject getButtonPress(void);

    private:
        ScreenObject findPressedObject(int16_t x, int16_t y);
        bool _touchEventHandled;
        Coordinate _screenWidth;
        Coordinate _screenHeight;
        sensitiveScreenField *firstNodePtr;
};
