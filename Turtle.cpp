/*   _____________________________________________________________________________________________
    |   This is the constructor for the Turtle class - contains the colours array                 | 
    |   and the methods used for turtle graphics, screen background and text                      |
    |_____________________________________________________________________________________________|  */
 

#include "Turtle.h"
#include <Adafruit_ILI9341.h> // LCD driver for TFT shield

ColorMap Turtle::colorList[] =
{
  {"green", 0, 255, 0},
  {"forest", 10, 80, 30},
  {"olive", 128, 128, 0},
  {"teal", 55, 145, 145},
  {"cyan", 0, 255, 255},
  {"blue", 0, 0, 255},
  {"navy", 0, 0, 128},
  {"magenta", 255, 0, 255}, 
  {"purple", 155, 50, 255},
  {"maroon", 140, 25, 100},
  {"mauve", 90, 15, 125},
  {"brown", 140, 70, 20},
  {"beige", 180, 150, 100},
  {"gold", 205, 173, 0},
  {"orange", 255, 140, 0},
  {"yellow", 255, 255, 0},
  {"pink", 255, 128, 128},
  {"red", 255, 0, 0,},
  {"white", 255, 255, 255},
  {"silver", 190, 190, 190},
  {"gray", 110, 110, 110},
  {"black", 0, 0, 0}
};

const int Turtle::colorListLength = 22; 

int Turtle::findColor(const char *name) // given a colour name returns the index of the colour
// inside the colorList array. If the colour is not found, returns -1.
{
  for (int i = 0; i < colorListLength; i++)
  {
    if (strcmp(colorList[i].name, name) == 0) // strcmp is a string comparison function
                                             // if it returns 0 the strings are the same
    {
      return i; // the name matched
    }
  }
    return -1; // colour name did not match
}

const char *Turtle::getColorName(int i) // given the index of a colour, return its name
{
  if((i<0) || (i >= Turtle::colorListLength))
  {
  return "No such color";
  }
  return Turtle::colorList[i].name;  
}

// constructor for TFT Turtle
Turtle::Turtle(Adafruit_ST7735 *tft)
{  
  m_tft = tft;
  m_x = m_tft->width()/2; // middle x screen coordinate 
  m_y = m_tft->height()/2; // middle y screen coordinate
  m_heading = 90/360 * (2*TURTLE_PI);
  m_penDown = true;
  m_screenColor = ILI9341_BLACK;
  m_penColor = ILI9341_RED;
  m_textColor = ILI9341_BLACK;
  m_savedX = m_x;
  m_savedY = m_y;
}

  void Turtle::left(float degrees)
  {
    //Translate degrees to radians
    float rads = (degrees / 360.0) * (2 * TURTLE_PI);
    //Adjust heading    
    m_heading -=rads;
  }
  
   void Turtle::right(float degrees)
  {
    //Translate degrees to radians
    float rads = (degrees / 360.0) * (2 * TURTLE_PI);
    //Adjust heading
    m_heading +=rads;
  }
  
  void Turtle::forward(float distance)
  { 
    float newx = (m_x + (cos(m_heading))*distance);
    float newy = (m_y + (sin(m_heading))*distance);
    if (m_penDown== true)
    {
     m_tft-> drawLine(m_x, m_y,newx, newy,m_penColor);
    }
    m_x = newx;
    m_y = newy;
  }    
 
 void Turtle::back(float distance)
 {
  float newx = (m_x - (cos(m_heading))*distance);
  float newy = (m_y - (sin(m_heading))*distance);
  if (m_penDown == true)
 {
  m_tft-> drawLine(m_x, m_y, newx, newy, m_penColor);
 }
  m_x = newx;
  m_y = newy; 
 }
 
  void Turtle::penUp()
  {
    m_penDown = false;
  }
  
  void Turtle::penDown()
  {
    m_penDown = true;
  }  
  
  void Turtle::moveTo(int x, int y)
  {
    m_x = x;
    m_y = y;
  }
  
  void Turtle::home()
  {
   m_x = m_tft->width()/2; // middle x screen coordinate 
   m_y = m_tft->height()/2; // middle y screen coordinate
  }
  
  void Turtle::clear()
  {
   m_tft-> fillScreen(m_screenColor);
  }

  void Turtle::setHeading(int degrees)
  {
   
   degrees = 360 - degrees;
   m_heading = ((2*PI) / 360) * degrees;
  }
  
    void Turtle::setPenColor(int color)
  {
  m_penColor = color;
  }
  
   void Turtle::setPenColor(int r, int g, int b) // uses Adafruit's color565 method to set colour given RGB components
   {
     setPenColor(m_tft->color565(r,g,b));
   }
   
      void Turtle::setPenColor(const char *color)
   {
     // look up the colour by name
     int colorindex = Turtle::findColor(color);
     if (colorindex == -1)
     return; // if colour not found do nothing
     
     // retrieve the red, green blue components
     int r = Turtle::colorList[colorindex].r;
     int g = Turtle::colorList[colorindex].g;
     int b = Turtle::colorList[colorindex].b;
     
     // set the colour
     setPenColor(r,g,b);
   }
   
       void Turtle::setScreenColor(int color)
  {
  m_screenColor = color;
  m_tft->fillScreen(m_screenColor);
  }
  
   void Turtle::setScreenColor(int r, int g, int b) // uses Adafruit's color565 method to set colour given RGB components
   {
     setScreenColor(m_tft->color565(r,g,b)); 
   }
 
  
   void Turtle::setScreenColor(const char *color)
   {
     // look up the colour by name
     int colorindex = (Turtle::findColor(color));
     if (colorindex == -1)
     {
     return; // colour not found
     } 
     
     // retrieve the red, green blue components
     int r = Turtle::colorList[colorindex].r;
     int g = Turtle::colorList[colorindex].g;
     int b = Turtle::colorList[colorindex].b;
     
     // set the colour
     setScreenColor(r,g,b); 
   }
  
     
  void Turtle::write(String text)
  {
    m_tft-> print(text);
  }
  
  void Turtle::setTextSize(int size)
  {
    if ((size < 1 || size > 4)) // text size range is 1 to 4
    {
      return;
    }
   m_tft-> setTextSize(size); 
  }
  
  void Turtle::setTextColor(int color)
  {
    m_textColor = color;
    m_tft-> setTextColor(m_textColor);
  }
  
  void Turtle::setTextColor(int r, int g, int b) // uses Adafruit's color565 method to set colour given RGB components
  {
   setTextColor(m_tft->color565(r, g, b)); 
  }
  
  void Turtle::setTextColor(const char *color)
   {
     // look up the colour by name
     int colorindex = Turtle::findColor(color);
     if (colorindex == -1)
     return; // if colour not found do nothing
     
     // retrieve the red, green blue components
     int r = Turtle::colorList[colorindex].r;
     int g = Turtle::colorList[colorindex].g;
     int b = Turtle::colorList[colorindex].b;
     
     // set the colour
     setTextColor(r,g,b); 
   }
  
  
  void Turtle::setTextLocation(int x, int y)
  {
    m_tft->setCursor(x, y);
  }
  
  void Turtle::polygon(float sides, float sideLength)
  {
    for (int s = 0; s < sides; s++)
    {
      forward(sideLength);
      right(360.0 / sides);
    }
  }
  
  void Turtle::star(int sides, float sideLength, float angle)
  {
    // oversteer angle to make a star
    // increase to make stars pointier
    // decrease to zero to draw regular n-gon
    
    for (int s = 0; s < sides; s++)
    {
      right(angle); // oversteer toward centre
      forward(sideLength / 2); // draw arm toward centre
      left(angle); // undo prior oversteer
      forward(sideLength / 2); // draw arm away from centre
      right(360 / sides);
    }
  }
  
 void Turtle::arcRight(float arcLength, int degrees)
 {
   float stepcount = abs(arcLength);
 for (int i = 0; i < stepcount; i++)
   {
   forward(arcLength / stepcount);
   right(degrees / stepcount);
   }
 }
 
 void Turtle::arcLeft(float arcLength, int degrees)
{
  arcRight(arcLength, -degrees);
} 
