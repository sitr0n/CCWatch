#pragma once
#include "position2d.h"
#include "Arduino.h"
#include "IGFX.h"

#define TEXT_WIDTH 6
#define TEXT_HEIGHT 7

class GFXdriver : public IGFX {
    public:
        GFXdriver();
        ~GFXdriver() = default;

        virtual void fill_rect(Color, Position2D);
        virtual void fill_circle(Color, Position2D);
        virtual void print(String text, Color, Position2D);
};
