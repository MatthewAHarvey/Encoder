// Version 1.0
// Button Handler class. This handles debouncing of a button and returns button down, up, double-click and hold events. Hold events can not work if the button is used in an interrupt routine.

#ifndef ButtonHandler_h
#define ButtonHandler_h

#include "MilliTimer.h"
#include "arduino.h"

enum class buttonEnum{
    NO_CHANGE = 0,
    BUTTON_UP, 
    BUTTON_DOWN, 
    BUTTON_DOUBLECLICK, 
    BUTTON_HOLD
};

class ButtonHandler{
public:
    ButtonHandler();
    ButtonHandler(uint8_t buttonPin);
    uint16_t getButtonHoldTime();
    uint16_t getDoubleClickMax();
    uint16_t getDebounceTime();
    bool getEnabledState();

    void init();
    void init(uint8_t buttonPin);
    buttonEnum poll();
    void enableButton();
    void disableButton();
    void setButtonHoldTime(uint16_t t);
    void setDoubleClickMax(uint16_t t);
    void setDebounceTime(uint16_t t);

private:
    uint8_t buttonPin;
    bool buttonEnabled = true;
    bool oldButtonState = true;
    bool buttonState = true;

    uint16_t buttonDebounceTime = 10;
    uint16_t doubleClickMax = 500;
    uint16_t buttonHoldMin = 1000;

    // timers
    MilliTimer buttonDebounceTimer;
    MilliTimer buttonHoldTimer;
    MilliTimer buttonDoubleClickTimer;

};

#endif