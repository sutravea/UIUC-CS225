#include "rgbapixel.h"

RGBAPixel::RGBAPixel()
{
  red = 255;
  green = 255;
  blue = 255;
  alpha = 255;
}

RGBAPixel::RGBAPixel (unsigned char red, unsigned char green, unsigned char blue)
{
  RGBAPixel::red = red;
  RGBAPixel::green = green;
  RGBAPixel::blue = blue;
}
