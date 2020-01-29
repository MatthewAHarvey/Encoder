#include "Enc.h"

Enc::Enc(){

}

Enc::Enc(uint8_t pinA, uint8_t pinB){
    this->pinA = pinA;
    this->pinB = pinB;
}

void Enc::init(){
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
}

void Enc::init(uint8_t pinA, uint8_t pinB){
    this->pinA = pinA;
    this->pinB = pinB;
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
}

encEnum Enc::poll(){
    AB = AB << 2; // Shift the old AB data two places to the left.
    AB |= (digitalRead(pinA) << 1) | digitalRead(pinB); // Add in the new AB data
    AB &= 0xF; // Mask with B00001111 to remove really old data so that we are left only with old AB and new AB.
    switch(encStateTable[AB]){
        case encStepEnum::CW_CHANGE:       stepCounter++;      break;
        case encStepEnum::ACW_CHANGE:      stepCounter--;      break;
        case encStepEnum::ILLEGAL_CHANGE:  stepCounter = 0;    break;
    }
    switch(stepCounter){
        case -4:    stepCounter = 0;    return encEnum::ACW;
        case 4:     stepCounter = 0;    return encEnum::CW;
        default:                        return encEnum::NO_CHANGE;
    }
}

void Enc::setReversedDirection(bool reverse){
    if(reverse != reversed){
        // need to flip the pins
        reversed = reverse;
        uint8_t tmp = pinB;
        pinB = pinA;
        pinA = tmp;    
    }
}

bool Enc::getReversedDirection(){
    return reversed;
}