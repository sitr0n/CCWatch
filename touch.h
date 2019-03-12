#pragma once
#include "position2d.h"
#include <Adafruit_STMPE610.h>
/*
 * This class constructs reponsive areas on a touch screen
 * and stores them internally. If an interesting area is touched,
 * then the tick function will return the corresponding ID which
 * was given by the constructor parameters.
 */
typedef int ButtonId;

class Touch {
    public:
        Touch(ButtonId id, Position2D position);
        ~Touch();
        
        static void init(Coordinate screenWidth, Coordinate screenHeight);
        static ButtonId tick();
        static void clearAllButtons();
        
    private:
        static ButtonId findPressedButton(int16_t x, int16_t y);
        
        ButtonId _id;
        Position2D _position;
        Touch * nextButton;
        
        static Touch * firstButtonPtr;
        static bool _touchEventHandled;
        static Coordinate _screenWidth;
        static Coordinate _screenHeight;
        static Adafruit_STMPE610 screen;
};
