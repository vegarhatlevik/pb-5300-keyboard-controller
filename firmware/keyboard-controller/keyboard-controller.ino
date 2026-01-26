#include <HID.h>

/*

*/

#include "Keyboard.h"

#define DEBUG

#define MAX_COLS 4
#define MAX_ROWS 4

#define ROW_1 2
#define ROW_2 3
#define ROW_3 4
#define ROW_4 5
/*
#define ROW_5 6
#define ROW_6 7
#define ROW_7 8
#define ROW_8 9

#define _SRCLR 21
#define _OE 20
#define RCLK 19
#define SER 18
#define _DETECT 14
#define SRCLK 16
*/

#define _COL_2 6
#define _COL_3 7
#define _COL_4 8
#define _COL_5 9

#define _CLED 15 // active low

#define KEY_PWR 0xFF // This should be handled specially, but not sure yet how.
#define KEY_NONE 0 // Not really needed because it will never be detected

#define KEY_X 'x'
#define KEY_C 'c'
#define KEY_Z 'z'
#define KEY_V 'v'
#define KEY_S 's'
#define KEY_D 'd'
#define KEY_A 'a'
#define KEY_F 'f'

void initOutput(uint8_t pin) {
  setHigh(pin);
}

void initInputPullup(uint8_t pin) {
  pinMode(pin, INPUT_PULLUP);
}

void initInput(uint8_t pin) {
  pinMode(pin, INPUT);
}

void setLow(uint8_t pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);  
}

void setHigh(uint8_t pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
}

uint8_t read(uint8_t pin) {
  pinMode(pin, INPUT_PULLUP);
  return digitalRead(pin); 
}

void setup() {
  uint8_t outputPins[] = {_CLED, _COL_2, _COL_3, _COL_4, _COL_5};
  uint8_t inputPullupPins[] = {ROW_1, ROW_2, ROW_3, ROW_4};

  for (uint8_t i=0; i<sizeof(outputPins); i++) {
    initOutput(outputPins[i]);
  }

  for (uint8_t i=0; i<sizeof(inputPullupPins); i++) {
    initInputPullup(inputPullupPins[i]);
  }

  Keyboard.begin();
}

void loop() {
  static const uint8_t columns[MAX_COLS]={_COL_2, _COL_3, _COL_4, _COL_5};
  static const uint8_t rows[MAX_ROWS]={ROW_1, ROW_2, ROW_3, ROW_4};

  static const uint8_t keyMatrix[MAX_ROWS][MAX_COLS] = {
    {KEY_ESC, KEY_NONE, KEY_F11, KEY_NONE},
    {KEY_F2, KEY_F3, KEY_F1, KEY_F4},
    {KEY_X, KEY_C, KEY_Z, KEY_V},
    {KEY_S, KEY_D, KEY_A, KEY_F}
  };

  static uint8_t previousMatrix[MAX_COLS][MAX_ROWS] = {{1}};
  static uint8_t readMatrix[MAX_COLS][MAX_ROWS] = {{1}};
 
  // Scan one column at a time by setting it's control line low
  // and reading the input pin for each row
  for (uint8_t column=0; column<MAX_COLS; column++) {
    setLow(columns[column]);
    delayMicroseconds(50);
    for (uint8_t row=0; row<MAX_ROWS; row++) {
      readMatrix[row][column] = read(rows[row]);
      // if (readMatrix[i][j] == 0) {
      //   Keyboard.write(keyMatrix[i][j]);
      // }
    }
    setHigh(columns[column]);
  }
  // Compare the read matrix to the previous matrix to determine what has changed.
  // If something has changed, send the corresponding key action and remember the
  // new value for the next scan.
  for (uint8_t column=0; column<MAX_COLS; column++) {
    for (uint8_t row=0; row<MAX_ROWS; row++) {
      if (readMatrix[row][column] != previousMatrix[row][column]) {
        uint8_t keyCode = keyMatrix[row][column];
        if (readMatrix[row][column] == 1) {
          Keyboard.release(keyCode);
          debugPrint("Key released: ", row, column, keyCode);

        } else {
          Keyboard.press(keyCode);
          debugPrint("Key pressed: ", row, column, keyCode);
        }
        previousMatrix[row][column] = readMatrix[row][column];
      }
    }
  }
}

void debugPrint(String s, uint8_t row, uint8_t column, uint8_t keyCode) {
#ifdef DEBUG
  char c = keyCode;
  String str = s + "row=" + row + ", column=" + column + ", " + String(keyCode) + ", " + String(c) + "\n";
  Serial.print(str.c_str());
#endif
}