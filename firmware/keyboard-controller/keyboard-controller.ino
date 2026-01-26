//#include <HID.h>

#include "PowerBook5300Keyboard.h"

PowerBook5300Keyboard kbd;

void setup() {
  kbd.init();
}

void loop() {
  kbd.scan();
}

