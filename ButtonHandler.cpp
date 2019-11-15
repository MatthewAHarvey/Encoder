#include "ButtonHandler.h"

ButtonHandler::ButtonHandler(){

}

ButtonHandler::ButtonHandler(uint8_t buttonPin){
    this->buttonPin = buttonPin;
}

uint16_t ButtonHandler::getButtonHoldTime(){
    return buttonHoldMin;
}

uint16_t ButtonHandler::getDoubleClickMax(){
    return doubleClickMax;
}

uint16_t ButtonHandler::getDebounceTime(){
    return buttonDebounceTime;
}

bool ButtonHandler::getEnabledState(){
    return buttonEnabled;
}

void ButtonHandler::init(uint8_t buttonPin){
    this->buttonPin = buttonPin;
    this->init();
}

void ButtonHandler::init(){
    pinMode(buttonPin, INPUT_PULLUP);
    buttonDebounceTimer.updateTimeOut(buttonDebounceTime);
    buttonHoldTimer.updateTimeOut(buttonHoldMin);
    buttonDoubleClickTimer.updateTimeOut(doubleClickMax);
}

buttonEnum ButtonHandler::poll(){
    if(buttonEnabled){
        oldButtonState = buttonState;
        buttonState = digitalRead(buttonPin);
        if(buttonState != oldButtonState && buttonDebounceTimer.timedOut(true)){
            // Button state has changed
            if(buttonState){ //Button has been pressed
                if(!buttonDoubleClickTimer.timedOut(true)){
                    return buttonEnum::BUTTON_DOUBLECLICK;
                }
                else{
                    buttonDoubleClickTimer.reset();
                    return buttonEnum::BUTTON_UP;
                }
            }
            else{ // Button has been pressed or released
                buttonHoldTimer.reset();
                return buttonEnum::BUTTON_DOWN;
            }
        }
        else if(!buttonState){ // button is being held down
            if(buttonHoldTimer.timedOut(true)){
                return buttonEnum::BUTTON_HOLD;
            }
        }
    }
    return buttonEnum::NO_CHANGE;
}

void ButtonHandler::enableButton(){
    buttonEnabled = true;
}

void ButtonHandler::disableButton(){
    buttonEnabled = false;
}

void ButtonHandler::setButtonHoldTime(uint16_t t){
    buttonHoldMin = t;
}

void ButtonHandler::setDoubleClickMax(uint16_t t){
    doubleClickMax = t;
}

void ButtonHandler::setDebounceTime(uint16_t t){
    buttonDebounceTime = t;
}
