#pragma once
#include "position2d.h"

enum Color {
  black = 0x0000,
  white = 0xFFFF,
  blue = 0x001F,
  red = 0xF800,
  green = 0x07E0
};

class IGFX {
    public:
        virtual void fill_rect(Color color, Position2D position) = 0;
        virtual void fill_circle(Color color, Position2D position) = 0;
        virtual void print(String text, Color color, Position2D position) = 0;
};
