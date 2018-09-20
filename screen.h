#pragma once

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "TouchInput.h"
#include "Display.h"

#define HOME_WINDOW 0
#define POPUP_WINDOW 1
#define CLOCK_WINDOW 2

#define ICON_HOME 1
#define ICON_BACK 2
#define ICON_FORWARD 3

#define FOOTER_TOP 280
#define FOOTER_EDGE_BUFFER 5
#define HEADER_BOT 40

class Screen {
    public:
        Screen();
        bool inputPoll();
        void buildDialogueBox(String title, String message, screenField position);

    private:

};
