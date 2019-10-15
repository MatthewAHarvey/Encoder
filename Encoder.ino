// Example program to show how the rotary encoder events are reported. 
#include "Encoder.h"        // Handles front panel rotary encoders

const uint8_t pinA = 4;
const uint8_t pinB = 5;
const uint8_t pinC = 6; // button pin

Encoder enc(pinA, pinB, pinC);

void setup(){
    Serial.begin(250000); // better to set the baud rate as high as possible since the processor then spends less time on blocking serial transmission. Also set it to a number that is a divisor of the processor clock speed to limit transmission errors. See any Atmega datasheet.
    enc.init();
}

void loop(){
  switch(enc.poll()){
    case NO_CHANGE:
      break;
    case CW_RATE1: 
      Serial.println("Clockwise Rotation, Rate 1");
      break;
    case CW_RATE2:
      Serial.println("Clockwise Rotation, Rate 2");
      break;
    case CW_RATE3:     
      Serial.println("Clockwise Rotation, Rate 3");
      break;
    case ACW_RATE1: 
      Serial.println("Anti-Clockwise Rotation, Rate 1");
      break;
    case ACW_RATE2: 
      Serial.println("Anti-Clockwise Rotation, Rate 2");
      break;
    case ACW_RATE3: 
      Serial.println("Anti-Clockwise Rotation, Rate 3");
      break;
    case BUTTON_UP:
      Serial.println("Button Released");
      break;
    case BUTTON_DOWN:
      Serial.println("Button Pressed");
      break;
    case BUTTON_DOUBLECLICK:
      Serial.println("Button Double-Clicked");
      break;
    case BUTTON_HOLD:
      Serial.println("Button Held Down");
      break;
  }
}