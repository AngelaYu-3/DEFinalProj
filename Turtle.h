// definition of Turtle class 
#ifndef Turtle_h
#define Turtle_h

#include"Arduino.h"
#include <Adafruit_ST7735.h> // LCD driver for TFT shield
#define TURTLE_PI 3.14159265 // pi is used to set turtle heading and turn turtle

struct ColorMap
{
  const char *name;
  int r;
  int g;
  int b;
};

class Turtle 
{
private:
  Adafruit_ST7735 *m_tft;
  float m_x; // x and y coordinates - start point for drawing 
  float m_y; 
  float m_heading; // direction in radians   
  bool m_penDown;
  int m_penColor;
  int m_screenColor;
  int m_textColor;
  static int findColor(const char *name);
  

public: 

  Turtle(Adafruit_ST7735 *tft); // constructor
  
  static const int colorListLength;
  static ColorMap colorList[];
  static const char *getColorName(int i);
  float m_savedX;
  float m_savedY;
  
  void forward(float distance);
  void back(float distance);
  void right(float degrees);
  void left(float degrees);
  void penUp();
  void penDown();
  void setPenColor(int color);
  void setPenColor(int r, int g, int b);
  void setPenColor(const char *color);
  void setScreenColor(int color);
  void setScreenColor(int r, int g, int b);
  void setScreenColor(const char *color);
  void moveTo(int x, int y);
  void home(); // moves turtle to centre of screen
  void setHeading(int degrees);
  void clear(); // fills screen with current m_color
  void write(String text);
  void setTextSize(int size);
  void setTextColor(int color);
  void setTextColor(int r, int g, int b);
  void setTextColor(const char *color);
  void setTextLocation(int x, int y);
  void polygon(float sides, float sideLength);
  void star(int sides, float sideLength, float angle);
  void arcRight(float arcLength, int degrees);
  void arcLeft(float arcLength, int degrees);
  
};

#endif
