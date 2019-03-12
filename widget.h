#pragma once
#include "IGFX.h"
#include "IINPUT.h"
#include "Arduino.h"

// STYLE
#define WINDOW_FRAME_WIDTH 5
#define WINDOW_HEADER_HEIGHT 40
#define EDGE_CURVE 20

class Widget {
    public:
        Widget(Color c, Position2D p);
        virtual ~Widget();
        virtual void draw() = 0;
        bool is_clicked();
        
        static void inject_graphics(IGFX* gfx);
        static void inject_input(IINPUT* input);
        static void tick();
        
    private:
        Color m_color;
        Position2D m_position;
        static IINPUT::Coordinate2D m_pressed_position;
        static IINPUT::Coordinate2D m_released_position;
        
    protected:
        Position2D get_position() const { return m_position; }
        Color get_color() const { return m_color; }
        static IGFX* m_gfx;
        static IINPUT* m_input;
};

class MockGFX : public IGFX {
    public:
        void fill_rect(Color, Position2D) { }
        void fill_circle(Color, Position2D) { }
        void print(String text, Color, Position2D) { }
};

class MockInput : public IINPUT {
    public:
        virtual Coordinate2D get_cursor() { }
        virtual bool is_pressed() { }
};
