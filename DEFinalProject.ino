/*
 * TODO:
 *   (1) fix code for resetting screen from completed to start to back (clearSwitchState)
 *   (2) code for how to get back to original screen--ie reset terminated
 *   (3) replace uno with nano
 */

#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h>
#include "turtleshapes.h"
#include <avr/pgmspace.h> 
#include "Turtle.h"

String goal = "WORKOUT";

//led pin inputs
const int in1 = 2, in2 = 4, in3 = 6, in4 = 8, in5 = 10, in6 = 12;

//led pin outputs
const int out1 = 3, out2 = 5, out3 = 7, out4 = 9, out5 = 11, out6 = 13;

//clear switch pin
const int clearLED = 6; 

//led states
int signals[7] = {1, 1, 1, 1, 1, 1, 1};
bool isSwitched[7] = {false, false, false, false, false, false, false};
bool isDone[7] = {false, false, false, false, false, false, false};
int dayX[7] = {10, 55, 100, 10, 55, 100, 55};
int dayY[7] = {35, 35, 35, 70, 70, 70, 105};

//other variables
int on = 1;
bool isReset = false;
int clearSwitch = 0;

#define TFT_CS 10
#define TFT_RST 9
#define TFT_DC 8
#define red 0x861F
#define green 0xCFF6

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Turtle t = Turtle(&tft);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);

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
  digitalWrite(out1, 0);
  digitalWrite(out2, 0); 

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
  for(int i = 0; i < 2; i++){
    if(!isDone[i]) return false;
  }return true;
}

void resetIsDone(){
  for(int i = 0; i < 2; i++){
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
  Serial.println(tft.width());
  Serial.println(tft.height());
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

      for(int i = 1; i < 3; i++){
        if(digitalRead(i * 2) == signals[i - 1]){
          digitalWrite((i * 2) + 1, HIGH);
          day(i - 1, green);
          isSwitched[i - 1] = true;
          isDone[i - 1] = true;
        }
        else{
          digitalWrite((i*2) + 1, LOW);
          day(i - 1, red);
          isDone[i - 1] = false;
        }
      }
  
    }  
  }
  
  else if(isAllDone()){
    switchClearState();
    int redo = clearSwitch;
    
    if(!isReset){
      tft.fillScreen(ST77XX_BLACK); 
      goalLine(goal);
      t.star(5, 30, 36); 
      isReset = true;
    }

    if(digitalRead(clearLED) == redo){
      resetOgScreen();
      resetIsDone();
      isReset = false;
    }
    
  }
}
