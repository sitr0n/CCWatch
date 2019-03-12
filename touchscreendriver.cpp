#include "touchscreendriver.h"
#include <SPI.h>
#include <Wire.h>

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 3800
#define TS_MAXX 100
#define TS_MINY 100
#define TS_MAXY 3750
#define STMPE_CS 32

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

TouchscreenDriver::TouchscreenDriver()
{
  m_input = Adafruit_STMPE610(STMPE_CS);
  m_input.begin();
}

IINPUT::Coordinate2D TouchscreenDriver::get_cursor()
{
  while(!m_input.bufferEmpty()) {
    m_input.readData(&x, &y, &z);
  }

  Coordinate2D scaled_data;
  scaled_data.x = map(x, TS_MINX, TS_MAXX, 0, SCREEN_WIDTH);
  scaled_data.y = map(y, TS_MINY, TS_MAXY, 0, SCREEN_HEIGHT);
  return scaled_data;
}

bool TouchscreenDriver::is_pressed()
{
  return m_input.touched();
}

