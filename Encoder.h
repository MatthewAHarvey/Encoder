#ifndef Encoder_h
#define Encoder_h

// Version 1.1 - Button Handler version and tidied up the state machine to make code more readable

// A simple to use rotary encoder class. Place the poll function in an interrupt routine or main code. Must be checked very regularly if in main code or it WILL miss events.

#include "MilliTimer.h"
#include "arduino.h"
#include "ButtonHandler.h"

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

enum class stepEnum : uint8_t{
    NO_CHANGE,
    CW_CHANGE,
    ACW_CHANGE,
    ILLEGAL_CHANGE
};

// Need to check the size of this and possibly shrink it. Possible it is taking up 16 bytes
const stepEnum stateTable[16] = {
    stepEnum::NO_CHANGE,        // 0000 0
    stepEnum::ACW_CHANGE,       // 0001 1
    stepEnum::CW_CHANGE,        // 0010 2
    stepEnum::ILLEGAL_CHANGE,   // 0011 3
    stepEnum::CW_CHANGE,        // 0100 4
    stepEnum::NO_CHANGE,        // 0101 5
    stepEnum::ILLEGAL_CHANGE,   // 0110 6
    stepEnum::ACW_CHANGE,       // 0111 7
    stepEnum::ACW_CHANGE,       // 1000 8
    stepEnum::ILLEGAL_CHANGE,   // 1001 9
    stepEnum::NO_CHANGE,        // 1010 10
    stepEnum::CW_CHANGE,        // 1011 11
    stepEnum::ILLEGAL_CHANGE,   // 1100 12
    stepEnum::CW_CHANGE,        // 1101 13
    stepEnum::ACW_CHANGE,       // 1110 14
    stepEnum::NO_CHANGE         // 1111 15
};

class Encoder
{
    public:
        Encoder(); // default to no pins so that we can define an array of them.
        Encoder(uint8_t pinA, uint8_t pinB);
        Encoder(uint8_t pinA, uint8_t pinB, uint8_t pinC);
        
        void init(); // Setup pins
        void init(uint8_t pinA, uint8_t pinB); 
        void init(uint8_t pinA, uint8_t pinB, uint8_t pinC);
        encoderEnum poll(bool rateless = false); // checks the state of the encoder and returns new steps if necessary. Call in pinchange interrupt routine or poll in main loop. If polling, do not including blocking code such as delay()!
        encoderEnum poll_rateless();

        unsigned int getButtonHoldTime();
        unsigned int getDoubleClickMax();
        unsigned int getDebounceTime();
        unsigned int getRate2Max();
        unsigned int getRate3Max();
        uint8_t getState();
        bool getReversedDirection();
        
        void setButtonHoldTime(unsigned int t);
        void setDoubleClickMax(unsigned int t);
        void setDebounceTime(unsigned int t);
        void setRate2Max(unsigned int t);
        void setRate3Max(unsigned int t);
        void setState(uint8_t state);
        void setReversedDirection(bool reverse);
        void enableButton();
        void disableButton();
        void enableEncoder();
        void disableEncoder();
        void enable();
        void disable();
    private:
        //pins
        uint8_t pinA;
        uint8_t pinB;
        uint8_t pinC;
        bool reversed = false;

        // Encoder enable state
        bool buttonEnabled = true;
        bool encoderEnabled = true;
        
        // button and encoder pin states
        uint8_t AB = 0xF;       // B1111 because the rotary encoder will be in neutral state and the pullups will make the readings high.
        // uint8_t ABold = 0xF;

        // See documentation for workings/logic of this lookup table
        
        encoderEnum encoderPoll();
        
        // button settings
        ButtonHandler button;

        // encoder settings
        unsigned int rate2Threshold = 125;
        unsigned int rate3Threshold = 25;

        // timers
        MilliTimer encoderTimer;

        int8_t stepCounter = 0;
};

#endif