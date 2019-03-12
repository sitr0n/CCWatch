#pragma once
//#include "position2d.h"

class IINPUT {
    public:
        struct Coordinate2D {
          int x = 0;
          int y = 0;
        };
        virtual Coordinate2D get_cursor() = 0;
        virtual bool is_pressed() = 0;
};
