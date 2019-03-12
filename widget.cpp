#include "widget.h"
IGFX* Widget::m_gfx = new MockGFX();
IINPUT* Widget::m_input = new MockInput();
IINPUT::Coordinate2D Widget::m_pressed_position;
IINPUT::Coordinate2D Widget::m_released_position;
        
Widget::Widget(Color color, Position2D position) :
  m_color(color),
  m_position(position)
{
  
}

Widget::~Widget()
{
  //m_gfx.fill_rect(black, _position);
}

void Widget::tick()
{
  if(m_input->is_pressed()) {
    m_pressed_position = m_input->get_cursor();
    Serial.println(m_pressed_position.x);
  } else {
    m_released_position = m_input->get_cursor();
  }
}

bool Widget::is_clicked()
{
  bool clicked = false;
  if(!m_input->is_pressed()){
    bool horizontal_pressed_check = (m_position.leftEdge < m_pressed_position.x) && (m_pressed_position.x < m_position.rightEdge);
    bool vertical_pressed_check = (m_position.topEdge < m_pressed_position.y) && (m_pressed_position.y < m_position.bottomEdge);
    bool horizontal_released_check = (m_position.leftEdge < m_released_position.x) && (m_released_position.x < m_position.rightEdge);
    bool vertical_released_check = (m_position.topEdge < m_released_position.y) && (m_released_position.y < m_position.bottomEdge);
    //Serial.println(m_pressed_position.x);
    if(horizontal_pressed_check && vertical_pressed_check && horizontal_released_check && vertical_released_check) {
      Serial.println(m_position.leftEdge);
      clicked = true;
    }
  }
  return clicked;
}


void Widget::inject_graphics(IGFX* gfx)
{
  delete m_gfx;
  m_gfx = gfx;
}

void Widget::inject_input(IINPUT* input)
{
  delete m_input;
  m_input = input;
}

