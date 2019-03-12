#include "apphome.h"
#include "machine.h"
#include "widget.h"


void AppHome::render()
{
  Position2D pos;
  pos.leftEdge = 10;
  pos.topEdge = 10;
  pos.rightEdge = 60;
  pos.bottomEdge = 60;
  
  Button w(red, pos);
  w.draw();
  
  pos.topEdge += 50;
  pos.bottomEdge += 50;
  btn = new Button(white, pos);
  btn->draw();
  
  pos.leftEdge = 60;
  pos.topEdge = 60;
  pos.rightEdge = 200;
  pos.bottomEdge = 80;
  TextBrowser tb("heey", blue, pos);
  tb.set_float(TextBrowser::Float::center);
  tb.draw();
}


void AppHome::tick(Machine &context)
{
  Widget::tick();
  if(btn->is_clicked()) {
    Position2D pos;
    pos.leftEdge = 100;
    pos.topEdge = 100;
    pos.rightEdge = 120;
    pos.bottomEdge = 120;
    
    Button w(green, pos);
    w.draw();
  }
}

