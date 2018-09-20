#include "screen.h"

Screen screen;

void setup() {
  static_assert(-5 / 2 == -2, "Rounding error");
}

void loop() {
  //bool ok = screen.inputPoll();
}
