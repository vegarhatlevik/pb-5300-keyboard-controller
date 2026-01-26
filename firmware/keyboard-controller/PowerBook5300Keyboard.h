class PowerBook5300Keyboard {
private:

  /////////////////////////////////////////////////////////////////////////////
  // Key definitions

  static const uint8_t KEY_PWR = 0xFF; // This should be handled specially, but not yet sure how.
  static const uint8_t KEY_NONE = 0; // Not really needed because it will never be detected.

  static const uint8_t KEY_X = 'x';
  static const uint8_t KEY_C = 'c';
  static const uint8_t KEY_Z = 'z';
  static const uint8_t KEY_V = 'v';
  static const uint8_t KEY_S = 's';
  static const uint8_t KEY_D = 'd';
  static const uint8_t KEY_A = 'a';
  static const uint8_t KEY_F = 'f';

  /////////////////////////////////////////////////////////////////////////////
  // Pin definitions

  static const uint8_t MAX_COLS = 4;
  static const uint8_t MAX_ROWS = 4;

  static const uint8_t ROW_1 = 2;
  static const uint8_t ROW_2 = 3;
  static const uint8_t ROW_3 = 4;
  static const uint8_t ROW_4 = 5;
  /*
  static const uint8_t ROW_5 = 6;
  static const uint8_t ROW_6 = 7;
  static const uint8_t ROW_7 = 8;
  static const uint8_t ROW_8 = 9;

  static const uint8_t _SRCLR = 21;
  static const uint8_t _OE = 20;
  static const uint8_t RCLK = 19;
  static const uint8_t SER = 18;
  static const uint8_t _DETECT = 14;
  static const uint8_t SRCLK = 16;
  */

  static const uint8_t _COL_2 = 6;
  static const uint8_t _COL_3 = 7;
  static const uint8_t _COL_4 = 8;
  static const uint8_t _COL_5 = 9;

  static const uint8_t _CLED = 15; // active low

  const uint8_t outputPins[5] = {_CLED, _COL_2, _COL_3, _COL_4, _COL_5};
  const uint8_t inputPullupPins[4] = {ROW_1, ROW_2, ROW_3, ROW_4};

  /////////////////////////////////////////////////////////////////////////////
  // Layout

  const uint8_t columns[MAX_COLS]={_COL_2, _COL_3, _COL_4, _COL_5};
  const uint8_t rows[MAX_ROWS]={ROW_1, ROW_2, ROW_3, ROW_4};

  uint8_t keyMatrix[MAX_ROWS][MAX_COLS];

  uint8_t previousMatrix[MAX_COLS][MAX_ROWS] = {{1}};
  uint8_t readMatrix[MAX_COLS][MAX_ROWS] = {{1}};

public:
  PowerBook5300Keyboard();
  void init();
  void scan();
};