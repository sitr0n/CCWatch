#include "screen.h"

//TouchInput *touch;

Screen::Screen()
{
  Display::Init();

  screenField db;
  db.leftEdge = 0;
  db.topEdge = 30;
  db.rightEdge = SCREEN_WIDTH;
  db.bottomEdge = SCREEN_HEIGHT - 30;
  String message = "Lorem ipsum dolor sit amet, eget curabitur elit arcu, curabitur sit et eleifend libero rhoncus, urna pede sed nisi sed, porttitor eu ac euismod aliquam suscipit. Taciti diam ullamcorper laoreet curabitur. Mus at iaculis praesentium nulla nunc, vel quis vel curabitur tempor. Volutpat sed in, convallis vivamus vestibulum sit dui pede.";
  buildDialogueBox("test", message, db);
}

void Screen::buildDialogueBox(String title, String message, screenField position)
{
  Display frame(blue, position);
  double frameCurve = 0.2;
  frame.setEdgeCurves(frameCurve);
  frame.draw();

  int frameWidth = 4;
  int titleBarHeight = 27;
  
  screenField titleArea;
  titleArea.leftEdge = position.leftEdge + frameWidth*(1 + frameCurve);
  titleArea.topEdge = position.topEdge + frameWidth;
  titleArea.rightEdge = position.rightEdge - frameWidth*(1 + frameCurve);
  titleArea.bottomEdge = titleArea.topEdge + titleBarHeight;
  Display titleBar(black, titleArea);
  int titleSize = 4;
  titleBar.PrintSection(title, titleSize, black);

  screenField bodyArea;
  bodyArea.leftEdge = position.leftEdge + frameWidth;
  bodyArea.topEdge = titleArea.bottomEdge + frameWidth;
  bodyArea.rightEdge = position.rightEdge - frameWidth;
  bodyArea.bottomEdge = position.bottomEdge - frameWidth;
  Display body(black, bodyArea);
  body.setEdgeCurves(frameCurve);
  body.draw();

  screenField textArea;
  textArea.leftEdge = bodyArea.leftEdge + frameWidth;
  textArea.topEdge = bodyArea.topEdge + frameWidth;
  textArea.rightEdge = bodyArea.rightEdge - frameWidth;
  int buttonHeight = 35;
  textArea.bottomEdge = bodyArea.bottomEdge - buttonHeight - frameWidth;
  Display text(black, textArea);
  int textSize = 2;
  String unprintedText = text.PrintSection(message, textSize, white);

  screenField declineButtonArea;
  declineButtonArea.leftEdge = textArea.leftEdge;
  declineButtonArea.topEdge = bodyArea.bottomEdge - buttonHeight;
  declineButtonArea.rightEdge = textArea.leftEdge + (textArea.rightEdge - textArea.leftEdge)/2 - frameWidth/2;
  declineButtonArea.bottomEdge = bodyArea.bottomEdge - frameWidth;
  Display declineButton(red, declineButtonArea);
  declineButton.setEdgeCurves(1);
  declineButton.draw();

  screenField acceptButtonArea;
  acceptButtonArea.leftEdge = textArea.rightEdge - (textArea.rightEdge - textArea.leftEdge)/2 + frameWidth/2 ;
  acceptButtonArea.topEdge = bodyArea.bottomEdge - buttonHeight;
  acceptButtonArea.rightEdge = textArea.rightEdge;
  acceptButtonArea.bottomEdge = bodyArea.bottomEdge - frameWidth;
  Display acceptButton(green, acceptButtonArea);
  acceptButton.setEdgeCurves(1);
  acceptButton.draw();
}

/*
bool Screen::inputPoll()
{
  ScreenObject button = touch->getButtonPress();
  screenField position;
  int textFieldWidth = 50;
  position.leftEdge = SCREEN_WIDTH/2 - textFieldWidth;
  position.topEdge = 100;
  position.rightEdge = SCREEN_WIDTH/2 + textFieldWidth;
  position.bottomEdge = 120;
  switch(button) {
    case ICON_HOME:

      break;
    case ICON_BACK:

      break;
    case ICON_FORWARD:

      break;
  }
  
  return false;
}
*/


