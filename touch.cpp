#include "touch.h"
#include <SPI.h>
#include <Wire.h>

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 3800
#define TS_MAXX 100
#define TS_MINY 100
#define TS_MAXY 3750
#define STMPE_CS 32

Touch * Touch::firstButtonPtr = nullptr;
bool Touch::_touchEventHandled = false;
Coordinate Touch::_screenWidth = 240;
Coordinate Touch::_screenHeight = 320;
Adafruit_STMPE610 Touch::screen = Adafruit_STMPE610(STMPE_CS);

Touch::Touch(ButtonId id, Position2D position) :
_id(id),
_position(position),
nextButton(nullptr)
{
  if (firstButtonPtr == nullptr) {
    firstButtonPtr = this;
  } else {
    auto * node = firstButtonPtr;
    while(node->nextButton != nullptr) {
      node = node->nextButton;
    }
    node->nextButton = this;
  }
}

Touch::~Touch()
{
  if (this == firstButtonPtr) {
    if (this->nextButton != nullptr) {
      firstButtonPtr = firstButtonPtr->nextButton;
    } else {
      firstButtonPtr = nullptr;
    }
  } else {
    auto * node = firstButtonPtr;
    while (node->nextButton != nullptr) {
      if (node->nextButton == this) {
        node->nextButton = this->nextButton;
        break;
      }
      node = node->nextButton;
    }
  }
}

void Touch::init(Coordinate screenWidth, Coordinate screenHeight)
{
  _screenWidth = screenWidth;
  _screenHeight = screenHeight;
  if (!screen.begin()) {
    Serial.println("Couldn't start touchscreen controller");
    while (true);
  }
}

ButtonId Touch::findPressedButton(int16_t x, int16_t y)
{
  ButtonId found = 0;
  auto * node = firstButtonPtr;
  do {
    bool leftCheck = node->_position.leftEdge <= (int)x;
    bool topCheck = node->_position.topEdge <= (int)y;
    bool rightCheck = node->_position.rightEdge >= (int)x;
    bool bottomCheck = node->_position.bottomEdge >= (int)y;
    if (leftCheck && topCheck && rightCheck && bottomCheck) {
      found = node->_id;
    }
    node = node->nextButton;
  } while (node != NULL);
  return found;
}

void Touch::clearAllButtons()
{
  if (firstButtonPtr != nullptr) {
    auto *trailNode = firstButtonPtr;
    do {
      auto *nodeToDelete = trailNode;
      trailNode = trailNode->nextButton;
      delete nodeToDelete;
    } while (trailNode != nullptr);
  } else {
    Serial.println("No buttons to clear");
  }
}

ButtonId Touch::tick()
{
  uint16_t x, y;
  uint8_t z;
  if (screen.touched() && _touchEventHandled == false) {
    screen.writeRegister8(STMPE_INT_STA, 0xFF);
    delay(50);
    while (screen.bufferEmpty() == false) {
      screen.readData(&x, &y, &z);
    }

    // Scale from ~0->4000 to tft.width using the calibration #'s
    x = map(x, TS_MINX, TS_MAXX, 0, _screenWidth);
    y = map(y, TS_MINY, TS_MAXY, 0, _screenHeight);
    ButtonId id = (firstButtonPtr == nullptr) ? 0 : findPressedButton(x, y);
    
    _touchEventHandled = true;
    return id;
  } else if (!screen.touched()) {
    _touchEventHandled = false;
    return 0;
  } else {
    screen.readData(&x, &y, &z); //Discarding buffer data
    return 0;
  }
}
