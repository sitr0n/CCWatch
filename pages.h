#pragma once
#include "components.h"

#define FOOTER_TOP 280
#define FOOTER_EDGE_BUFFER 5
#define HEADER_BOT 40

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

class Pages {
    public:
        Pages(screenField position) : _position(position) {};
        ~Pages(){Components::clearAllButtons();};
        static void Init(){Components::Init(SCREEN_WIDTH, SCREEN_HEIGHT);};

        static void tick();
        
        virtual void display() = 0;
        void dialogueBox(String title, String text);
    private:
        screenField _position;
};

class DialogueBox : public Pages {
    public:
        DialogueBox(String title, String text, screenField position) : Pages(position), _title(title), _text(text) {};
        virtual void display() {dialogueBox(_title, _text);};
    private:
        String _title, _text;
};

class HomeScreen : public Pages {
    public:
        HomeScreen(screenField position) : Pages(position) {};
        virtual void display() {};
};

class SomeScreen : public Pages {
    public:
        SomeScreen(screenField position) : Pages(position) {};
        virtual void display() {};
};
