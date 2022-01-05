/*
 * TODO:
 *   (1) reset only clears and flips on/off signal of LEDs that are on--does NOT effect all LEDs
 *   (2) connect switch signals to LCD display (instead of LEDs)
 */


//led pin inputs
const int in1 = 2, in2 = 4, in3 = 6, in4 = 8, in5 = 10, in6 = 12;

//led pin outputs
const int out1 = 3, out2 = 5, out3 = 7, out4 = 9, out5 = 11, out6 = 13;

//clear switch pin
const int clearLED = A0; 

//led states
int signals[7] = {1, 1, 1, 1, 1, 1, 1};
bool isSwitched[7] = {false, false, false, false, false, false, false};

//other variables
int on = 1;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);

  pinMode(clearLED, INPUT);
  
}

void clearAll(){
  digitalWrite(out1, 0);
  digitalWrite(out2, 0); 

  for(int i = 0; i < 7; i++){
    if(isSwitched[i]) flipSignal(i);
  }
}

void flipSignal(int index){
  if(signals[index] == 1) signals[index] = 0;
  else signals[index] = 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //Serial.print("on: ");
  //Serial.println(on);
  //Serial.println(analogRead(clearLED));
    
  if(analogRead(clearLED) == 1023){
    clearAll();
    //if(!isFlip) flipSignal();
    //isFlip = true;
  }
  else{
    //isFlip = false;

    /*for(int i = 0; i < 7; i++){
      if(digitalRead('in' + i) == signals[i - 1]){
        digitalWrite('out' + i, HIGH);
        isSwitched[i] = true;
        //flipSignal(i - 1);
      }
      else digitalWrite('out' + i, LOW);
    }
    
      int j = 1;
      Serial.println('in' + j);
      Serial.println(digitalRead('in' + j);

    */

    if(digitalRead(in1) == signals[0]){
      digitalWrite(out1, HIGH);
      isSwitched[0] = true;
      //flipSignal(0);
    }
    else digitalWrite(out1, LOW);
  
    if(digitalRead(in2) == signals[1]){
      digitalWrite(out2, HIGH);
      isSwitched[1] = true;
      //flipSignal(1);
    }
    else digitalWrite(out2, LOW);
  }
  
}
