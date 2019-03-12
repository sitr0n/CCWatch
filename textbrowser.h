#pragma once
#include "Arduino.h"
#include "widget.h"

#define TEXT_WIDTH 6
#define TEXT_HEIGHT 7

class TextBrowser : public Widget {
    public:
        TextBrowser(String text, Color c, Position2D p) : m_text(text), Widget(c, p) { }
        virtual ~TextBrowser() = default;
        virtual void draw() {
          auto position = Widget::get_position();
          int textSize = (position.getHeight() + 1)/TEXT_HEIGHT;
          int textSpace = m_text.length()*textSize*TEXT_WIDTH;
          int vacantSpace = position.getWidth();
          int unusedSpace = vacantSpace - textSpace;
          
          switch (m_align) {
            case Float::center :
              position.leftEdge += unusedSpace/2;
              position.rightEdge -= unusedSpace/2;
            break;
            case Float::right :
              position.leftEdge += unusedSpace;
            break;
            case Float::left :
              position.rightEdge -= unusedSpace;
            break;
          }
          m_gfx->print(m_text, Widget::get_color(), position);
        };
        
        enum class Float { left, center, right };
        void set_float(Float f) { m_align = f; }
   
    private:
        String m_text;
        Float m_align{Float::left};
};
