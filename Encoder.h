#ifndef Encoder_h
#define Encoder_h

// Version 1.1 - Button Handler version and tidied up the state machine to make code more readable

// A simple to use rotary encoder class. Place the poll function in an interrupt routine or main code. Must be checked very regularly if in main code or it WILL miss events.

#include "arduino.h"
#include "Enc.h"
#include "ButtonHandler.h"
#include "MilliTimer.h"


//Uncomment following line to enable debugging serial comments.
#define DEBUG
#ifdef DEBUG
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x)  Serial.println(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
#endif

enum class encoderEnum : uint8_t{
    NO_CHANGE = 0,
    BUTTON_UP, 
    BUTTON_DOWN, 
    BUTTON_DOUBLECLICK, 
    BUTTON_HOLD,
    CW_RATE1, 
    CW_RATE2, 
    CW_RATE3, 
    ACW_RATE1, 
    ACW_RATE2, 
    ACW_RATE3
};

class Encoder{
    public:
        Encoder(); // default to no pins so that we can define an array of them.
        Encoder(uint8_t pinA, uint8_t pinB);
        Encoder(uint8_t pinA, uint8_t pinB, uint8_t pinC);
        
        void init(); // Setup pins
        void init(uint8_t pinA, uint8_t pinB); 
        void init(uint8_t pinA, uint8_t pinB, uint8_t pinC);
        encoderEnum poll(bool rateless = false); // checks the state of the encoder and returns new steps if necessary. Call in pinchange interrupt routine or poll in main loop. If polling, do not including blocking code such as delay()!
        encoderEnum poll_rateless();

        uint16_t getButtonHoldTime();
        uint16_t getDoubleClickMax();
        uint16_t getDebounceTime();
        uint16_t getRate2Max();
        uint16_t getRate3Max();
        uint8_t getState();
        bool getReversedDirection();
        
        void setButtonHoldTime(uint16_t t);
        void setDoubleClickMax(uint16_t t);
        void setDebounceTime(uint16_t t);
        void setRate2Max(uint16_t t);
        void setRate3Max(uint16_t t);
        void setState(uint8_t state);
        void setReversedDirection(bool reverse);
        void enableButton();
        void disableButton();
        void enableEncoder();
        void disableEncoder();
        void enable();
        void disable();
    private:
        // button 
        ButtonHandler button;
        // encoder
        Enc encoder;
        MilliTimer encoderTimer;
        uint16_t rate2Threshold = 125;
        uint16_t rate3Threshold = 25;

        // Encoder enable state
        bool buttonEnabled = true;
        bool encoderEnabled = true;        
};

#endif