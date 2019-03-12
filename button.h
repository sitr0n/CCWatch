#pragma once
#include "Arduino.h"
#include "widget.h"


class Button : public Widget {
    public:
        Button(Color color, Position2D position) : Widget(color, position) { }
        virtual void draw() { Widget::m_gfx->fill_rect(Widget::get_color(), Widget::get_position()); }
        
    private:
};
