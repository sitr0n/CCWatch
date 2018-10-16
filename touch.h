/*
 * This class constructs reponsive areas on a touch screen
 * and stores them internally. If an interesting area is touched,
 * then the tick function will return the corresponding ID which
 * was given by the constructor parameters.
 */
#pragma once
#include "screenfield_struct.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_STMPE610.h>

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 3800
#define TS_MAXX 100
#define TS_MINY 100
#define TS_MAXY 3750
#define STMPE_CS 32

typedef int ButtonID;

class Touch {
    public:
        Touch(ButtonID id, screenField position);
        ~Touch();
        static void Init(Coordinate screenWidth, Coordinate screenHeight);
        static ButtonID tick();
        static void clearAllButtons();
        
    private:
        static ButtonID findPressedButton(int16_t x, int16_t y);
        
        ButtonID _id;
        screenField _position;
        Touch * nextButton;
        
        static Touch * firstButtonPtr;
        static bool _touchEventHandled;
        static Coordinate _screenWidth;
        static Coordinate _screenHeight;
        static Adafruit_STMPE610 screen;
};
