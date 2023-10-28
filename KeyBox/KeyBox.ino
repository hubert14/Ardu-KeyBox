#include <Joystick.h> // https://github.com/MHeironimus/ArduinoJoystickLibrary v2.1.1
#include <EncButton.h> // https://github.com/GyverLibs/EncButton v2.0

#define EB_NO_COUNTER
#define PHYSICAL_BUTTONS_COUNT 5

#define BUTTONS_COUNT 15

#define BUTTONS_START_PIN 2
#define ENCODER_1_START_PIN 8
#define ENCODER_2_START_PIN 14

#define POT_1_PIN A0
#define POT_2_PIN A1

EncButton<EB_TICK, ENCODER_1_START_PIN, ENCODER_1_START_PIN+1, ENCODER_1_START_PIN+2> enc_1;
EncButton<EB_TICK, ENCODER_2_START_PIN, ENCODER_2_START_PIN+1, ENCODER_2_START_PIN+2> enc_2;

Joystick_ Joystick(
  0x03,
  JOYSTICK_TYPE_JOYSTICK,
  BUTTONS_COUNT,
  0,
  true,
  true,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false
);

void setup() {
  for(int i = BUTTONS_START_PIN; i < BUTTONS_START_PIN+BUTTONS_COUNT; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  // Serial.begin(9600);
  Joystick.begin();
}

int lastButtonState[4];

int previousPot_1_Val = 0;
int previousPot_2_Val = 0;

unsigned long current_millis = 0;
unsigned long update_millis = 0;
unsigned long enc_1_millis[5];
unsigned long enc_2_millis[5];
unsigned long enc_hold[2];
bool enc_turned[2];
bool enc_holded[2];
bool enc_joy_state[2];
byte enc_state[2];

void loop() {
  current_millis = millis();
  enc_1.tick();
  enc_2.tick();
  if(current_millis % 50 == 0) {
    checkPots();
    checkButtons();
    checkEncoders();
  }
}

void checkPots() {
  int pot_1_Val = analogRead(POT_1_PIN);
  if(pot_1_Val < previousPot_1_Val -2 || pot_1_Val > previousPot_1_Val + 2) {
    Joystick.setXAxis(pot_1_Val);
    // Serial.print("Pot1: ");
    // Serial.println(pot_1_Val);
    previousPot_1_Val = pot_1_Val;
  }

  int pot_2_Val = analogRead(POT_2_PIN);
  if(pot_2_Val < previousPot_2_Val -2 || pot_2_Val > previousPot_2_Val + 2) {
    Joystick.setYAxis(pot_2_Val);
    // Serial.print("Pot2: ");
    // Serial.println(pot_2_Val);
    previousPot_2_Val = pot_2_Val;
  }
}

void checkButtons() {
  for (int index = BUTTONS_START_PIN; index < PHYSICAL_BUTTONS_COUNT + BUTTONS_START_PIN; index++)
  {
    int currentButtonState = !digitalRead(index);
    if (currentButtonState != lastButtonState[index])
    {
      Joystick.setButton(index, currentButtonState);
      // Serial.print("Button clicked | ");
      // Serial.print(currentButtonState);
      // Serial.print(" | ");
      // Serial.println(index);
      lastButtonState[index] = currentButtonState;
    }
  }
}

void checkEncoders() {
  for(int i = 1; i <= 5; i++) {
    if(enc_1_millis[i-1] != 0 && current_millis - enc_1_millis[i-1] > 25) {
      Joystick.setButton(PHYSICAL_BUTTONS_COUNT + i-1, 0);
      enc_1_millis[i-1] = 0;
      if(i == 5) {
        enc_joy_state[0] = 0;
      }
    }
  }

  for(int i = 1; i <= 5; i++) {
    if(enc_2_millis[i-1] != 0 && current_millis - enc_2_millis[i-1] > 25) {
      Joystick.setButton(PHYSICAL_BUTTONS_COUNT + i+4, 0);
      enc_2_millis[i-1] = 0;
      if(i == 5) {
        enc_joy_state[1] = 0;
      }
    }
  }

  // ---------- ENCODER 1
  if(enc_1.left() || enc_1.leftH()) {
    enc_state[0] = 1;
  }
  else if(enc_1.right() || enc_1.rightH()) {
    enc_state[0] = 2;
  }
  else if(enc_1.press()) {
    enc_state[0] = 3;
  }
  else if(enc_1.release()) {
    enc_state[0] = 4;
  }
  else enc_state[0] = 0;
  
  unsigned long hold_val_1 = current_millis - enc_hold[0];
  switch(enc_state[0]) {
    case 0:
      if(enc_holded[0]) {
        if(!enc_turned[0] && hold_val_1 > 600 && !enc_joy_state[0]) {
          Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 4, 1);
          // Serial.print("hold");
          enc_joy_state[0] = true;
        }
      }
      break;
    case 1:
      if(enc_holded[0]) {
        Joystick.setButton(PHYSICAL_BUTTONS_COUNT, 1);
        enc_1_millis[0] = current_millis;
        // Serial.println("LeftH trigger");
        enc_turned[0] = true;
      } else {
        Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 1, 1);
        enc_1_millis[0] = current_millis;
        // Serial.println("left trigger");
      }
      break;
    case 2:
      if(enc_holded[0]) {
        Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 2, 1);
        enc_1_millis[2] = current_millis;
        // Serial.println("RightH trigger");
        enc_turned[0] = true;
      } else {
        Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 3, 1);
        enc_1_millis[3] = current_millis;
        // Serial.println("right trigger");
      }
      break;
    case 3:
      enc_hold[0] = current_millis;
      enc_holded[0] = true;
      // Serial.println("press");
      break;
    case 4:
      // Serial.println("release");
      
      if(!enc_turned[0] && hold_val_1 < 350 && hold_val_1 > 70) {
          Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 4, 1);
          // Serial.print("click");
        }
      
      enc_holded[0] = false;
      enc_1_millis[4] = current_millis;
      enc_turned[0] = false;
      enc_hold[0] = 0;
      break;
    
  }

  // ---------- ENCODER 2
  if(enc_2.left() || enc_2.leftH()) {
    enc_state[1] = 1;
  }
  else if(enc_2.right() || enc_2.rightH()) {
    enc_state[1] = 2;
  }
  else if(enc_2.press()) {
    enc_state[1] = 3;
  }
  else if(enc_2.release()) {
    enc_state[1] = 4;
  }
  else enc_state[1] = 0;
  
  unsigned long hold_val = current_millis - enc_hold[1];
  switch(enc_state[1]) {
    case 0:
      if(enc_holded[1]) {
        if(!enc_turned[1] && hold_val > 600 && !enc_joy_state[1]) {
          Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 9, 1);
          // Serial.print("hold");
          enc_joy_state[1] = true;
        }
      }
      break;
    case 1:
      if(enc_holded[1]) {
        Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 5, 1);
        enc_2_millis[0] = current_millis;
        // Serial.println("LeftH trigger");
        enc_turned[1] = true;
      } else {
        Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 6, 1);
        enc_2_millis[1] = current_millis;
        // Serial.println("left trigger");
      }
      break;
    case 2:
      if(enc_holded[1]) {
        Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 7, 1);
        enc_2_millis[2] = current_millis;
        // Serial.println("RightH trigger");
        enc_turned[1] = true;
      } else {
        Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 8, 1);
        enc_2_millis[3] = current_millis;
        // Serial.println("right trigger");
      }
      break;
    case 3:
      enc_hold[1] = current_millis;
      enc_holded[1] = true;
      // Serial.println("press");
      break;
    case 4:
      // Serial.println("release");
      
      if(!enc_turned[1] && hold_val < 600 && hold_val > 70) {
          Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 9, 1);
          // Serial.print("click");
        }
      
      enc_holded[1] = false;
      enc_2_millis[4] = current_millis;
      enc_turned[1] = false;
      enc_hold[1] = 0;
      break;
    
  } 
}