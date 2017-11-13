/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#ifndef EH1_CONFIG_H
#define EH1_CONFIG_H

#include "../config.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x3078
#define MANUFACTURER    Maple Computing
#define PRODUCT         Lets Split EH1
#define DESCRIPTION     An enhanced Lets split
#define DEVICE_VER      0x0001

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

/* ECO V1 pin-out */
#define MATRIX_ROW_PINS { D3, E6, F4, F5 }
#define MATRIX_COL_PINS { B0, F0, F1, C7, B6, B5 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* ws2812 RGB LED */
//#define RGB_DI_PIN D3
//#define RGBLIGHT_TIMER
//#define RGBLED_NUM 12    // Number of LEDs

/* Backlight LEDs */
#define BACKLIGHT_PIN B7
#define BACKLIGHT_LEVELS 3


#endif
