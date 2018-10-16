#include "pages.h"

void setup() {
  static_assert(-5 / 2 == -2, "Rounding error");
  Serial.begin(115200);
  Pages::Init();

  screenField dbArea;
  dbArea.leftEdge = 0;
  dbArea.topEdge = 0;
  dbArea.rightEdge = SCREEN_WIDTH;
  dbArea.bottomEdge = SCREEN_HEIGHT;
  String text = "Lorem ipsum dolor sit amet, eget curabitur elit arcu, curabitur sit et eleifend libero rhoncus, urna pede sed nisi sed, porttitor eu ac euismod aliquam suscipit. Taciti diam ullamcorper laoreet curabitur. Mus at iaculis praesentium nulla nunc, vel quis vel curabitur tempor. Volutpat sed in, convallis vivamus vestibulum sit dui pede.";
  DialogueBox db("test", text, dbArea);
  db.display();
  while(true) {
    db.tick();
  }
}

void loop() {
  
}
