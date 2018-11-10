#include "machine.h"

void setup() {
  Serial.begin(115200);

  Machine machine;

  while (machine.GetRunning()) {
    machine.tick();
  }
  
}

void loop() {

}
