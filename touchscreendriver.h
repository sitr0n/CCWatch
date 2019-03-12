#pragma once
#include "iinput.h"
#include <Adafruit_STMPE610.h>

class TouchscreenDriver : public IINPUT {
    public:
        TouchscreenDriver();
        virtual Coordinate2D get_cursor();
        virtual bool is_pressed();
    private:
        Adafruit_STMPE610 m_input;
        bool m_pressed;
        uint16_t x, y;
        uint8_t z;
};
