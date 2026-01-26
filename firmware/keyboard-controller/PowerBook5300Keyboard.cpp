// I don't know why I need to define USBCON. My board is definitely supported.
// I have a Sparkfun Pro Micro, which is Leonardo compatible. Yet, I get an error
// that my board is not supported if I don't define USBCON. I even tried with an
// actual Leonrdo board, and I have the same problem. So, I will leave this define
// here until I understand what is going wrong. With the define, it works fine.
#define USBCON
// Even if US layout is the default, you get a compiler warning if you don't define it.
#define HID_CUSTOM_LAYOUT
#define LAYOUT_US_ENGLISH
#include <HID-Project.h>

#include "PowerBook5300Keyboard.h"
#include "InputOutputTools.h"

#define DEBUG

static void debugPrint(String s, uint8_t row, uint8_t column, uint8_t keyCode) {
#ifdef DEBUG
  char c = keyCode;
  String str = s + "row=" + row + ", column=" + column + ", " + String(keyCode) + ", " + String(c) + "\n";
  Serial.print(str.c_str());
#endif
}

PowerBook5300Keyboard::PowerBook5300Keyboard() : keyMatrix ({
    {KEY_ESC, KEY_NONE, KEY_F11, KEY_NONE},
    {KEY_F2, KEY_F3, KEY_F1, KEY_F4},
    {KEY_X, KEY_C, KEY_Z, KEY_V},
    {KEY_S, KEY_D, KEY_A, KEY_F}
  })
  {}

void PowerBook5300Keyboard::init() {
  ;
  for (uint8_t i=0; i<sizeof(outputPins); i++) {
    InputOutputTools::initOutput(outputPins[i]);
  }
  for (uint8_t i=0; i<sizeof(inputPullupPins); i++) {
    InputOutputTools::initInputPullup(inputPullupPins[i]);
  }
  BootKeyboard.begin();
}

void PowerBook5300Keyboard::scan() {
  // Scan one column at a time by setting it's control line low
  // and reading the input pin for each row
  for (uint8_t column=0; column<MAX_COLS; column++) {
    InputOutputTools::setLow(columns[column]);
    delayMicroseconds(50);
    for (uint8_t row=0; row<MAX_ROWS; row++) {
      readMatrix[row][column] = InputOutputTools::read(rows[row]);
    }
    InputOutputTools::setHigh(columns[column]);
  }
  // Compare the read matrix to the previous matrix to determine what has changed.
  // If something has changed, send the corresponding key action and remember the
  // new value for the next scan.
  for (uint8_t column=0; column<MAX_COLS; column++) {
    for (uint8_t row=0; row<MAX_ROWS; row++) {
      if (readMatrix[row][column] != previousMatrix[row][column]) {
        uint8_t keyCode = keyMatrix[row][column];
        if (readMatrix[row][column] == 1) {
          BootKeyboard.release(keyCode);
          debugPrint("Key released: ", row, column, keyCode);

        } else {
          BootKeyboard.press(keyCode);
          debugPrint("Key pressed: ", row, column, keyCode);
        }
        previousMatrix[row][column] = readMatrix[row][column];
      }
    }
  }
  // Check the status of the CapsLock LED
  if (BootKeyboard.getLeds() & LED_CAPS_LOCK) {
    // LED should be on
    InputOutputTools::setLow(_CLED);
  } else {
    // LED should be off
    InputOutputTools::setHigh(_CLED);
  }
}