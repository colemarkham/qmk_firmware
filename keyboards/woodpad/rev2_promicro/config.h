/*
Copyright 2017 Cole Markham

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef REV2_PROMICRO_CONFIG_H
#define REV2_PROMICRO_CONFIG_H

/* USB Device descriptor parameter */
#define DEVICE_VER      0x0002

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
#define MATRIX_ROW_PINS { B1, E6, B3, B4, B2 }
#define MATRIX_COL_PINS { F4, F5, F6, F7 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL, or CUSTOM_MATRIX */
#define DIODE_DIRECTION COL2ROW

#define CATERINA_BOOTLOADER

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCING_DELAY 5


#endif
