#ifndef Enc_h
#define Enc_h

#include "arduino.h"

enum class encStepEnum : uint8_t{
    NO_CHANGE,
    CW_CHANGE,
    ACW_CHANGE,
    ILLEGAL_CHANGE
};

// Need to check the size of this and possibly shrink it. Possible it is taking up 16 bytes
const encStepEnum encStateTable[16] = {
    encStepEnum::NO_CHANGE,        // 0000 0
    encStepEnum::ACW_CHANGE,       // 0001 1
    encStepEnum::CW_CHANGE,        // 0010 2
    encStepEnum::ILLEGAL_CHANGE,   // 0011 3
    encStepEnum::CW_CHANGE,        // 0100 4
    encStepEnum::NO_CHANGE,        // 0101 5
    encStepEnum::ILLEGAL_CHANGE,   // 0110 6
    encStepEnum::ACW_CHANGE,       // 0111 7
    encStepEnum::ACW_CHANGE,       // 1000 8
    encStepEnum::ILLEGAL_CHANGE,   // 1001 9
    encStepEnum::NO_CHANGE,        // 1010 10
    encStepEnum::CW_CHANGE,        // 1011 11
    encStepEnum::ILLEGAL_CHANGE,   // 1100 12
    encStepEnum::CW_CHANGE,        // 1101 13
    encStepEnum::ACW_CHANGE,       // 1110 14
    encStepEnum::NO_CHANGE         // 1111 15
};

enum class encEnum : uint8_t{
    NO_CHANGE = 0,
    CW, 
    ACW
};

class Enc{
public:
    Enc();
    Enc(uint8_t pinA, uint8_t pinB);

    void init();
    void init(uint8_t pinA, uint8_t pinB);

    encEnum poll();

    void setReversedDirection(bool reverse);
    bool getReversedDirection();

private:
    uint8_t pinA;
    uint8_t pinB;
    bool reversed = false;

    // encoder pin states and rotation step
    // Lower nibble gives the current state.
    uint8_t AB = 0xF;       // B1111 because the rotary encoder will be in neutral state and the pullups will make the readings high.
    int8_t stepCounter = 0;
};

#endif