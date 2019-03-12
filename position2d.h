#pragma once
#include "Arduino.h"

typedef int Coordinate;
struct Position2D {
  Coordinate leftEdge{0};
  Coordinate topEdge{0};
  Coordinate rightEdge{0};
  Coordinate bottomEdge{0};

  void setWidth(Coordinate width)
  {
    auto center = getCenterX();
    leftEdge = center - width/2;
    rightEdge = center + width/2;
  }

  Coordinate getShortestSide()
  {
    auto width = getWidth();
    auto height = getHeight();
    return (width >= height) ? height : width;
  }

  void setHeight(Coordinate height)
  {
    auto center = getCenterY();
    topEdge = center - height/2;
    bottomEdge = center + height/2;
  }

  Coordinate getWidth()
  {
    return (rightEdge - leftEdge);
  }

  Coordinate getHeight()
  {
    return (bottomEdge - topEdge);
  }

  Coordinate getCenterX()
  {
    return (leftEdge + getWidth()/2);
  }

  Coordinate getCenterY()
  {
    return (topEdge + getHeight()/2);
  }
};
