#pragma once

#include "screenfield_struct.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CS   15
#define TFT_DC   33
#define SD_CS    14

#define TEXT_WIDTH 6
#define TEXT_HEIGHT 7

enum Colors {
  black = 0x0000,
  white = 0xFFFF,
  blue = 0x001F,
  red = 0xF800,
  green = 0x07E0
};

class Graphics {
    public:
        Graphics(Colors color, screenField position) : _color(color), _position(position) {};
        virtual ~Graphics() = default;
        
        static void init();
        virtual void display() = 0;
        
        void Print(String text);
        void fillRect(void);
        void fillCircle(void);
        
    private:
        screenField _position;
        Colors _color;
};

class Text : public Graphics {
    public:
        Text(String text, Colors color, screenField position) : Graphics(color, position), _text(text) {};
        virtual ~Text() = default;
        virtual void display(){
          Print(_text);
        };
    private:
        String _text;
};

class Rectangle : public Graphics {
    public:
        Rectangle(Colors color, screenField position) : Graphics(color, position) {};
        virtual ~Rectangle() = default;
        virtual void display(){
          fillRect();
        };
};

class Circle : public Graphics {
    public:
        Circle(Colors color, screenField position) : Graphics(color, position) {};
        virtual ~Circle() = default;
        virtual void display(){
          fillCircle();
        };
};
