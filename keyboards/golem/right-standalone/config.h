/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 8

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/
#define MATRIX_ROW_PINS { D4, D6, D7, B4, B5 }
#define MATRIX_COL_PINS_RIGHT { B2, B3, B7, B1, F5, F4, F6, F7 }
#define UNUSED_PINS

// FIXME change this based on split backspace state
#define DRIVER_1_LED_TOTAL 44
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL
