#pragma once
#include "touch.h"
#include "graphics.h"

// STYLE
#define WINDOW_FRAME_WIDTH 5
#define WINDOW_HEADER_HEIGHT 40
#define EDGE_CURVE 20

class Components {
    public:
        Components(Colors color, screenField position) : _color(color), _position(position) {};
        static void Init(int screenWidth, int screenHeight){Graphics::Init(); Touch::Init(screenWidth, screenHeight);};
        virtual void display() = 0;
        
        static void clearAllButtons(){Touch::clearAllButtons();};
        
        void window(String title);
        String textField(String text, int textSize);
        void button(int id, String buttonText);
    private:
        void fillSurface(Colors color, screenField position);
        String println(String text, Colors color, int fontSize, screenField position);

        Colors _color;
        screenField _position;
};

class Window : public Components {
    public:
        Window(String title, Colors color, screenField position) : Components(color, position), _title(title) {};
        virtual void display(){window(_title);};
    private:
        String _title;
};

class Button : public Components {
    public: 
        Button(int id, Colors color, screenField position) : Components(color, position), _id(id), _buttonText("") {};
        virtual void display(){
            button(_id, _buttonText);
        };
        static bool pollButtons();
        void setButtonText(String text){_buttonText = text;};
    private:
        int _id;
        String _buttonText;
};

class Textfield : public Components {
    public:
        Textfield(String text, Colors color, screenField position) : Components(color, position), _text(text), _textSize(1) {};
        virtual void display(){
            _text = textField(_text, _textSize);
        };
        void setTextSize(int size){_textSize = size;};
    private:
        String _text;
        int _textSize;
};
