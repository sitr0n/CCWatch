#include "TouchInput.h"

static Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

TouchInput::TouchInput(Coordinate screenWidth, Coordinate screenHeight) :
_screenWidth(screenWidth),
_screenHeight(screenHeight),
_touchEventHandled(false),
firstNodePtr(NULL)
{
  if (!ts.begin()) {
    Serial.println("Couldn't start touchscreen controller");
    while (true);
  }
}

void TouchInput::addButton(Coordinate leftEdge,
                            Coordinate topEdge,
                            Coordinate rightEdge,
                            Coordinate bottomEdge,
                            ScreenObject id)
{
  // assert unique id, and within range
  // assert no overlaping pixels
  if (firstNodePtr == NULL) {
    firstNodePtr = new sensitiveScreenField;
  }
  auto *endNodePtr = firstNodePtr;
  while (endNodePtr->next != NULL) {
    endNodePtr = endNodePtr->next;
    assert(endNodePtr->id != id);
  }
  endNodePtr->next = new sensitiveScreenField;
  endNodePtr->next->id = id;
  endNodePtr->next->leftEdge = leftEdge;
  endNodePtr->next->topEdge = topEdge;
  endNodePtr->next->rightEdge = rightEdge;
  endNodePtr->next->bottomEdge = bottomEdge;
}

ScreenObject TouchInput::findPressedObject(int16_t x, int16_t y)
{
  ScreenObject found = 0;
  sensitiveScreenField *node = firstNodePtr;

  do {
    bool leftCheck = node->leftEdge <= (int)x;
    bool topCheck = node->topEdge <= (int)y;
    bool rightCheck = node->rightEdge >= (int)x;
    bool bottomCheck = node->bottomEdge >= (int)y;
    if (leftCheck && topCheck && rightCheck && bottomCheck) {
      found = node->id;
    }
    node = node->next;
  } while (node != NULL);
  return found;
}

ScreenObject TouchInput::getButtonPress()
{
  uint16_t x, y;
  uint8_t z;
  if (ts.touched() && _touchEventHandled == false) {
    ts.writeRegister8(STMPE_INT_STA, 0xFF);
    delay(50);
    while (ts.bufferEmpty() == false) {
      ts.readData(&x, &y, &z);
    }

    // Scale from ~0->4000 to tft.width using the calibration #'s
    x = map(x, TS_MINX, TS_MAXX, 0, _screenWidth);
    y = map(y, TS_MINY, TS_MAXY, 0, _screenHeight);
    
    ScreenObject fieldID = findPressedObject(x, y);
    _touchEventHandled = true;
    return fieldID;
  } else if (!ts.touched()) {
    _touchEventHandled = false;
    return 0;
  } else {
    ts.readData(&x, &y, &z); //Discarding buffer data
    return 0;
  }
}

