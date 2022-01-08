/*
 * TODO:
 *   (1) replace uno with nano,
 */

#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h>
#include "turtleshapes.h"
#include <avr/pgmspace.h> 
#include "Turtle.h"

String goal = "WORKOUT";
int numSwitches = 7;

//led pin inputs
const int in1 = 2, in2 = 3, in3 = 4, in4 = 5, in5 = 6, in6 = 7, in7 = 8;

//led pin outputs
//const int out1 = 3, out2 = 5, out3 = 7, out4 = 9, out5 = 11, out6 = 13;

//clear switch pin
const int clearLED = 9; 

//led states
int signals[7] = {1, 1, 1, 1, 1, 1, 1};
bool isSwitched[7] = {false, false, false, false, false, false, false};
bool isDone[7] = {false, false, false, false, false, false, false};
int dayX[7] = {10, 55, 100, 10, 55, 100, 55};
int dayY[7] = {35, 35, 35, 70, 70, 70, 105};

//other variables
int on = 1;
bool isReset1 = false;
bool isReset2 = false;
int clearSwitch = 1;

#define TFT_CS A4
#define TFT_RST A3
#define TFT_DC A2
#define red 0x861F
#define green 0xCFF6

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Turtle t = Turtle(&tft);

void setup() {
  // put your setup code here, to run once:
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  /*pinMode(in3, INPUT);
  pinMode(in4, INPUT);
  pinMode(in5, INPUT);
  pinMode(in6, INPUT);
  pinMode(in7, INPUT);*/

  pinMode(clearLED, INPUT);

  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST77XX_BLACK);
  Serial.println(tft.width());
  Serial.println(tft.height());
  tft.setRotation(-45);
  goalLine(goal);

  for(int i = 0; i < 7; i++){
    day(i, red);
  }
  
}

void clearAll(){

  for(int i = 0; i < 7; i++){
    if(isSwitched[i]){
      flipSignal(i);
      isSwitched[i] = false;
    }
  }
}

void flipSignal(int index){
  if(signals[index] == 1) signals[index] = 0;
  else signals[index] = 1;
}

void goalLine(String goal){
  tft.setCursor(3, 4);
  tft.setTextWrap(true);
  tft.setTextSize(2);
  tft.print(goal);
}

void day(int day, uint16_t color){
  tft.setCursor(dayX[day], dayY[day]);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.setTextSize(3);
  
  if(day == 0) tft.print("M");
  else if(day == 1) tft.print("T");
  else if(day == 2) tft.print("W");
  else if (day == 3) tft.print("T");
  else if (day == 4) tft.print("F");
  else if (day == 5) tft.print("S");
  else if (day == 6) tft.print("S");
}

bool isAllDone(){
  for(int i = 0; i < numSwitches; i++){
    if(!isDone[i]) return false;
  }return true;
}

void resetIsDone(){
  for(int i = 0; i < 7; i++){
    isDone[i] = false;
  }
}

void switchClearState(){
  if(clearSwitch == 0) clearSwitch = 1;
  else clearSwitch = 0;
}

void resetOgScreen(){
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(-45);
  goalLine(goal);

  for(int i = 0; i < 7; i++){
    day(i, red);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  if(!isAllDone()){
    if(digitalRead(clearLED) == on){
      clearAll();
      switchClearState();
      if(on == 1) on = 0;
      else on = 1;
    }
    else{

      for(int i = 2; i < numSwitches + 2; i++){
        if(digitalRead(i) == signals[i - 2]){
          //digitalWrite((i * 2) + 1, HIGH);
          day(i - 2, green);
          isSwitched[i - 2] = true;
          isDone[i - 2] = true;
        }
        else{
          //digitalWrite((i*2) + 1, LOW);
          day(i - 2, red);
          isDone[i - 2] = false;
        }
      }
  
    }  
  }
  
  else if(isAllDone()){
    
    if(!isReset1){
      delay(500);
      tft.fillScreen(ST77XX_BLACK); 
      goalLine(goal);
      t.moveTo(55, 40);
      t.setPenColor("cyan");
      t.star(5, 40, 45); 
      isReset1 = true;
      
    }else if (digitalRead(clearLED) == clearSwitch){
      delay(500);
      resetOgScreen();
      resetIsDone();
      switchClearState();
      isReset1 = false;
    }
    
  }
}
