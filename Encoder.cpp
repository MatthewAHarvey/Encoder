#include "Encoder.h"

Encoder::Encoder(){

}

Encoder::Encoder(uint8_t pinA, uint8_t pinB){
    encoder = Enc(pinA, pinB);
    buttonEnabled = false;
}

Encoder::Encoder(uint8_t pinA, uint8_t pinB, uint8_t pinC){
    encoder = Enc(pinA, pinB);
    button = ButtonHandler(pinC);
}

void Encoder::init(){
    encoder.init();
    if(buttonEnabled){
        button.init();
    }
}

void Encoder::init(uint8_t pinA, uint8_t pinB){
    encoder.init(pinA, pinB);
    buttonEnabled = false;
}

void Encoder::init(uint8_t pinA, uint8_t pinB, uint8_t pinC){
    encoder.init(pinA, pinB);
    button.init(pinC);
}

encoderEnum Encoder::poll(bool rateless){
    
    if(buttonEnabled){
        switch(button.poll()){
            case buttonEnum::BUTTON_UP:             return encoderEnum::BUTTON_UP;
            case buttonEnum::BUTTON_DOWN:           return encoderEnum::BUTTON_DOWN;
            case buttonEnum::BUTTON_DOUBLECLICK:    return encoderEnum::BUTTON_DOUBLECLICK;
            case buttonEnum::BUTTON_HOLD:           return encoderEnum::BUTTON_HOLD;
        }
    }

    if(encoderEnabled)
    {
        encEnum result = encoder.poll();
        uint16_t encoderTimeDiff= encoderTimer.elapsed();
        switch(result){
            case encEnum::ACW:
                // stepCounter = 0;
                // encoderTimeDiff = encoderTimer.elapsed();
                encoderTimer.reset();
                if(encoderTimeDiff < rate3Threshold && !rateless){
                    return encoderEnum::ACW_RATE3;
                }
                else if(encoderTimeDiff < rate2Threshold && !rateless){
                    return encoderEnum::ACW_RATE2;
                }
                else{
                    return encoderEnum::ACW_RATE1;
                }
                break;
            case encEnum::CW:
                // stepCounter = 0;
                // encoderTimeDiff = encoderTimer.elapsed();
                encoderTimer.reset();
                if(encoderTimeDiff < rate3Threshold && !rateless){
                    return encoderEnum::CW_RATE3;
                }
                else if(encoderTimeDiff < rate2Threshold && !rateless){
                    return encoderEnum::CW_RATE2;
                }
                else{
                    return encoderEnum::CW_RATE1;
                }
                break;
        }
    }
    return encoderEnum::NO_CHANGE;
}

encoderEnum Encoder::poll_rateless(){
    return poll(true);
}

uint16_t Encoder::getButtonHoldTime(){
    return button.getButtonHoldTime();
}

uint16_t Encoder::getDoubleClickMax(){
    return button.getDoubleClickMax();
}

uint16_t Encoder::getDebounceTime(){
    return button.getDebounceTime();
}

uint16_t Encoder::getRate2Max(){
    return rate2Threshold;
}

uint16_t Encoder::getRate3Max(){
    return rate3Threshold;
}

bool Encoder::getReversedDirection(){
    return encoder.getReversedDirection();
}

void Encoder::setButtonHoldTime(uint16_t t){
    button.setButtonHoldTime(t);
}

void Encoder::setDoubleClickMax(uint16_t t){
    button.setDoubleClickMax(t);
}

void Encoder::setDebounceTime(uint16_t t){
    button.setDebounceTime(t);
}

void Encoder::setRate2Max(uint16_t t){
    rate2Threshold = t;
}

void Encoder::setRate3Max(uint16_t t){
    rate3Threshold = t;
}

void Encoder::setState(uint8_t state){
    switch(state)
    {
        case 0:
            encoderEnabled = false;
            buttonEnabled = false;
            break;
        case 1:
            encoderEnabled = false;
            buttonEnabled = true;
            break;
        case 2:
            encoderEnabled = true;
            buttonEnabled = false;
            break;
        case 3:
            encoderEnabled = true;
            buttonEnabled = true;
            break;
        default:
            break;
    }
}

void Encoder::setReversedDirection(bool reverse){
    encoder.setReversedDirection(reverse);
}

uint8_t Encoder::getState(){
    if(buttonEnabled && encoderEnabled){ return 3; }
    else if(encoderEnabled)            { return 2; }
    else if(buttonEnabled)             { return 1; }
    else                               { return 0; }
}

void Encoder::enableButton(){
    buttonEnabled = true;
}

void Encoder::disableButton(){
    buttonEnabled = false;
}

void Encoder::enableEncoder(){
    encoderEnabled = true;
}

void Encoder::disableEncoder(){
    encoderEnabled = false;
}

void Encoder::enable(){
    buttonEnabled = true;
    encoderEnabled = true;
}

void Encoder::disable(){
    buttonEnabled = false;
    encoderEnabled = false;
}
