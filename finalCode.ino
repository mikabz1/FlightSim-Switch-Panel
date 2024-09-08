#include <Joystick.h>

//buttons consts and variabels.
const byte BTN_1 = 10;
const byte BTN_2 = 9;
const byte BTN_3 = 8;
const byte BTN_4 = 7;
const byte BTN_5 = 6;
const byte BTN_6 = 5;
const byte BTN_7 = 4;
const byte BTN_8 = 3;
const byte BTN_9 = 2;
const byte BTN_10 = 1;
const byte BTN_13 = A2;
const byte BTN_14 = A1;
const byte BTN_15 = A0;
const byte BTN_16 = 11;
const byte BTN_17 = 12;
const byte BTN_18 = 13;

int lastButtonState[19] = {LOW};

//potetiometer.
const byte POTEN = A3;
int potenLastVal;

//encoder variable.
const byte ENCODER_A = A4;
const byte ENCODER_B = A5;
static int PrevStateAB;
static int RotDir, RotVal = 0;
#define ROT_RESOLUTION 255

Joystick_ Joystick(0x06, JOYSTICK_TYPE_GAMEPAD, 64, 0,true);

//time variable.
unsigned long previusTime = millis();
unsigned long btnDebounceFreq = 30;

void setupPins(){
  for(int i = 1 ;i <= 13 ;i++){
    pinMode(i,INPUT_PULLUP);
  }

  pinMode(BTN_13 , INPUT);
  digitalWrite(BTN_13 , HIGH);
  pinMode(BTN_14 , INPUT);
  digitalWrite(BTN_14 , HIGH);
  pinMode(BTN_15 , INPUT);
  digitalWrite(BTN_15 , HIGH);

  pinMode(ENCODER_A , INPUT);
  pinMode(ENCODER_B , INPUT);
}
byte getButtonDigitalState(unsigned int buttonNumber){
  if(buttonNumber == 1){
    return digitalRead(BTN_1);
  }
  if(buttonNumber == 2){
    return digitalRead(BTN_2);
  }
  if(buttonNumber == 3){
    return digitalRead(BTN_3);
  }
  if(buttonNumber == 4){
    return digitalRead(BTN_4);
  }
  if(buttonNumber == 5){
    return digitalRead(BTN_5);
  }
  if(buttonNumber == 6){
    return digitalRead(BTN_6);
  }
  if(buttonNumber == 7){
    return digitalRead(BTN_7);
  }
  if(buttonNumber == 8){
    return digitalRead(BTN_8);
  }
  if(buttonNumber == 9){
    return digitalRead(BTN_9);
  }
  if(buttonNumber == 10){
    return digitalRead(BTN_10);
  }
  if(buttonNumber == 13){
    return digitalRead(BTN_13);
  }
  if(buttonNumber == 14){
    return digitalRead(BTN_14);
  }
  if(buttonNumber == 15){
    return digitalRead(BTN_15);
  }
  if(buttonNumber == 16){
    return digitalRead(BTN_16);
  }
  if(buttonNumber == 17){
    return digitalRead(BTN_17);
  }
  if(buttonNumber == 18){
    return digitalRead(BTN_18);
  }
  return 0;
}
void setup() {
  setupPins();
  Joystick.begin();
  potenLastVal = analogRead(POTEN);
  Joystick.setXAxisRange(-ROT_RESOLUTION, ROT_RESOLUTION);
  PrevStateAB = (digitalRead(ENCODER_A) << 1) | digitalRead(ENCODER_B);
}

bool setupFlag = true;

void loop() {
  //set up button states and send the info.
  if(setupFlag){
    for(int i = 1 ; i <= 18;i++){
      if(i == 11 || i == 12)continue;
      byte state = getButtonDigitalState(i);
      lastButtonState[i] = state;
      if(state == LOW){
        Joystick.setButton(i-1, HIGH);
      }
      else{
        Joystick.setButton(i-1, LOW);
      }
    }
    setupFlag = false;
  }

  //check each button state and handle the info.
  unsigned long currentTime = millis();
  if(currentTime - previusTime > btnDebounceFreq){
    previusTime += btnDebounceFreq;
    for(int i = 1 ; i <= 18;i++){
      if(i == 11 || i == 12)continue;
      byte state = getButtonDigitalState(i);
      if(state != lastButtonState[i]){
        lastButtonState[i] = state;
        if(state == HIGH){
          Joystick.releaseButton(i-1);
        }
        else{
          
          Joystick.pressButton(i-1);
        }
      }
    }
  }

  //encoder logic.
  int CurrStateAB;
  CurrStateAB = (digitalRead(ENCODER_A) << 1) | digitalRead(ENCODER_B);

  if (PrevStateAB != CurrStateAB)
  {
    int PrevCurrStateAB = (PrevStateAB << 2) | CurrStateAB;
    if ((PrevCurrStateAB == 0b1101) || (PrevCurrStateAB == 0b0010))
    {
      RotDir = 1;
    }
    else if ((PrevCurrStateAB == 0b1110) || (PrevCurrStateAB == 0b0001))
    {
      RotDir = -1;
    }
    else if ((PrevCurrStateAB == 0b0100) || (PrevCurrStateAB == 0b1011))
    {
      if ((RotDir == 1) && (RotVal < ROT_RESOLUTION))
      {
        RotVal++;
        Joystick.setXAxis(RotVal);
      }
    }
    else if ((PrevCurrStateAB == 0b1000) || (PrevCurrStateAB == 0b0111))
    {
      if ((RotDir == -1) && (RotVal > -ROT_RESOLUTION))
      {
        RotVal--;
        Joystick.setXAxis(RotVal);
      }
    }
    PrevStateAB = CurrStateAB;
  }

  // poten logic.
  currentTime = millis();
  if(currentTime - previusTime > btnDebounceFreq){
    int currentPotenVal = analogRead(POTEN);
    if(currentPotenVal + 5 > potenLastVal || currentPotenVal - 5 < potenLastVal ){
      potenLastVal = currentPotenVal;
      if(currentPotenVal < 20){
          Joystick.releaseButton(31);
          Joystick.releaseButton(32);
          Joystick.releaseButton(33);
          Joystick.releaseButton(34);
          Joystick.pressButton(30);
      }
      if(currentPotenVal >= 20 && currentPotenVal < 220){
          Joystick.releaseButton(30);
          Joystick.releaseButton(32);
          Joystick.releaseButton(33);
          Joystick.releaseButton(34);
          Joystick.pressButton(31);
      }
      if(currentPotenVal >= 220 && currentPotenVal < 420){
          Joystick.releaseButton(30);
          Joystick.releaseButton(31);
          Joystick.releaseButton(33);
          Joystick.releaseButton(34);
          Joystick.pressButton(32);
      }
      if(currentPotenVal >= 420 && currentPotenVal < 620){
          Joystick.releaseButton(30);
          Joystick.releaseButton(31);
          Joystick.releaseButton(32);
          Joystick.releaseButton(34);
          Joystick.pressButton(33);
      }
      if(currentPotenVal >= 620 && currentPotenVal < 820){
          Joystick.releaseButton(30);
          Joystick.releaseButton(31);
          Joystick.releaseButton(32);
          Joystick.releaseButton(33);
          Joystick.pressButton(34);
      }
    }
  }
}
