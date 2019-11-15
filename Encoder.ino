// Example program to show how the rotary encoder events are reported. 
#include "Encoder.h"        // Handles front panel rotary encoders
#include "MilliTimer.h"

const uint8_t pinA = 2;
const uint8_t pinB = 3;
const uint8_t pinC = 6; // button pin

Encoder enc(pinA, pinB, pinC);
Encoder enc1(pinA, pinB, pinC);
Encoder enc2(pinA, pinB, pinC);
Encoder enc3(pinA, pinB, pinC);
Encoder enc4(pinA, pinB, pinC);

void setup(){
    Serial.begin(250000); // better to set the baud rate as high as possible since the processor then spends less time on blocking serial transmission. Also set it to a number that is a divisor of the processor clock speed to limit transmission errors. See any Atmega datasheet.
    enc.init();
    enc1.init();
    enc2.init();
    enc3.init();
    enc4.init();

}
uint8_t i = 0;
void loop(){
  switch(enc.poll()){
    case encoderEnum::NO_CHANGE:
      break;
    case encoderEnum::CW_RATE1: 
      Serial.println("Clockwise Rotation, Rate 1");
      break;
    case encoderEnum::CW_RATE2:
      Serial.println("Clockwise Rotation, Rate 2");
      break;
    case encoderEnum::CW_RATE3:     
      Serial.println("Clockwise Rotation, Rate 3");
      break;
    case encoderEnum::ACW_RATE1: 
      Serial.println("Anti-Clockwise Rotation, Rate 1");
      break;
    case encoderEnum::ACW_RATE2: 
      Serial.println("Anti-Clockwise Rotation, Rate 2");
      break;
    case encoderEnum::ACW_RATE3: 
      Serial.println("Anti-Clockwise Rotation, Rate 3");
      break;
    case encoderEnum::BUTTON_UP:
      Serial.println("Button Released");
      break;
    case encoderEnum::BUTTON_DOWN:
      Serial.println("Button Pressed");
      break;
    case encoderEnum::BUTTON_DOUBLECLICK:
      Serial.println("Button Double-Clicked");
      break;
    case encoderEnum::BUTTON_HOLD:
      Serial.println("Button Held Down");
      break;
  }
  // 
  // switch(i++%10){
  //     case 0:
  //       break;
  //     case 1: 
  //       Serial.println("Clockwise Rotation, Rate 1");
  //       break;
  //     case 2:
  //       Serial.println("Clockwise Rotation, Rate 2");
  //       break;
  //     case 3:     
  //       Serial.println("Clockwise Rotation, Rate 3");
  //       break;
  //     case 4: 
  //       Serial.println("Anti-Clockwise Rotation, Rate 1");
  //       break;
  //     case 5: 
  //       Serial.println("Anti-Clockwise Rotation, Rate 2");
  //       break;
  //     case 6: 
  //       Serial.println("Anti-Clockwise Rotation, Rate 3");
  //       break;
  //     case 7:
  //       Serial.println("Button Released");
  //       break;
  //     case 8:
  //       Serial.println("Button Pressed");
  //       break;
  //     case 9:
  //       Serial.println("Button Double-Clicked");
  //       break;
  //     case 10:
  //       Serial.println("Button Held Down");
  //       break;
  //   }
}