# Encoder
A rotary encoder class library for Arduino. Encoder events are returned as an enum. Both clockwise and anti-clockwise rotations trigger events. The encoder can be rotated at three rates with unique enum entries being returned for each. This means you can use the encoder for both fine and coarse control of a power supply voltage for example. The class also handles button presses and recognises held down buttons and double-clicks. The rotation rates and button press timings are tunable. See `Encoder.h` for available class methods.

## Usage

See `Encoder.ino` for a very basic example program.

1. Place `#include "Encoder.h"` at the top of the `.ino` file.
2. Create a global Encoder variable.
3. Initialise the encoder with `init()` inside the `setup()` function.
4. Regularly poll the encoder to check its state. The best way is to attach the pins as change interrupts and call `poll()` when an interrupt is triggered. If this isn't possible, just be sure to call `poll()` regularly in the main `loop()` function.
5. Events are returned as an enum. See example for use.