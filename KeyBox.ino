#include <Joystick.h>
#include <EncButton.h>

#define PHYSICAL_BUTTONS_COUNT 5

#define BUTTONS_COUNT 15

#define BUTTONS_START_PIN 4
#define ENCODER_1_START_PIN 9
#define ENCODER_2_START_PIN 12

#define POT_1_PIN A0
#define POT_2_PIN A1

#define FIRST_BUTTON 0
#define ENC_1_LEFT_BTN 6
#define ENC_1_CLICK_BTN 7
#define ENC_1_RIGHT_BTN 8

#define ENC_2_LEFT_BTN 9
#define ENC_2_CLICK_BTN 10
#define ENC_2_RIGHT_BTN 11

#define ENC_1_HOLD_LEFT_BTN 12
#define ENC_1_HOLD_RIGHT_BTN 13

#define ENC_2_HOLD_LEFT_BTN 14
#define ENC_2_HOLD_RIGHT_BTN 15

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
  // Serial.println("start");
  Joystick.begin();
}

int lastButtonState[4];

int previousPot_1_Val = 0;
int previousPot_2_Val = 0;

unsigned long current_millis = 0;
unsigned long update_millis = 0;
unsigned long enc_1_millis[5];
unsigned long enc_2_millis[5];

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
    // Serial.println(pot_1_Val);
    previousPot_1_Val = pot_1_Val;
  }

  int pot_2_Val = analogRead(POT_2_PIN);
  if(pot_2_Val < previousPot_2_Val -2 || pot_2_Val > previousPot_2_Val + 2) {
    Joystick.setYAxis(pot_2_Val);
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

  for(int i = 1; i < 5; i++) {
    if(enc_1_millis[i-1] != 0 && current_millis - enc_1_millis[i-1] > 3) {
      Joystick.setButton(PHYSICAL_BUTTONS_COUNT + i, 0);
      enc_1_millis[i-1] = 0;
    }
  }

  for(int i = 1; i < 5; i++) {
    if(enc_2_millis[i-1] != 0 && current_millis - enc_2_millis[i-1] > 3) {
      Joystick.setButton(PHYSICAL_BUTTONS_COUNT + i, 0);
      enc_2_millis[i-1] = 0;
    }
  }

  // enc 1
  if(enc_1.leftH()) {
    Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 1, 1);
    enc_1_millis[0] = millis();
  }
  else if(enc_1.left()) {
    Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 2, 1);
    enc_1_millis[1] = millis();
  }

  if(enc_1.rightH()) {
    Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 3, 1);
    enc_1_millis[2] = millis();
  }
  else if(enc_1.right()) {
    Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 4, 1);
    enc_1_millis[3] = millis();
  }

  if(enc_1.click()) {
    Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 5, 1);
    enc_1_millis[4] = millis();
  }

  // enc 2
  if(enc_2.leftH()) {
    Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 6, 1);
    enc_2_millis[0] = millis();
  }
  else if(enc_2.left()) {
    Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 7, 1);
    enc_2_millis[1] = millis();
  }

  if(enc_2.rightH()) {
    Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 8, 1);
    enc_2_millis[2] = millis();
  }
  else if(enc_2.right()) {
    Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 9, 1);
    enc_2_millis[3] = millis();
  }

  if(enc_2.click()) {
    Joystick.setButton(PHYSICAL_BUTTONS_COUNT + 10, 1);
    enc_2_millis[4] = millis();
  }
}