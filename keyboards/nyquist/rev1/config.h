/*
Copyright 2017 Danny Nguyen <danny@hexwire.com>

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

#ifndef REV1_CONFIG_H
#define REV1_CONFIG_H

#include "../config.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xCEEB
#define PRODUCT_ID      0x1156
#define DEVICE_VER      0x0100
#define MANUFACTURER    Keebio
#define PRODUCT         The Nyquist Keyboard
#define DESCRIPTION     Split 60 percent ortholinear keyboard

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

// wiring of each half
#define MATRIX_ROW_PINS { D4, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { F6, F7, B1, B3, B2, B6 }

#define CATERINA_BOOTLOADER

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3

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
#define RGB_DI_PIN D3
#define RGBLIGHT_TIMER
#define RGBLED_NUM 16    // Number of LEDs
#define ws2812_PORTREG  PORTD
#define ws2812_DDRREG   DDRD

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#ifdef BROKEN_HALF
    #define KEYMAP( \
    	L00, L01, L02, L03, L04, L05, R00, R01, R02, R03, R04, R05, \
    	L10, L11, L12, L13, L14, L15, R10, R11, R12, R13, R14, R15, \
    	L20, L21, L22, L23, L24, L25, R20, R21, R22, R23, R24, R25, \
    	L30, L31, L32, L33, L34, L35, R30, R31, R32, R33, R34, R35, \
        L40, L41, L42, L43, L44, L45, R40, R41, R42, R43, R44, R45 \
    	) \
    	{ \
    		{ R05, R04, R03, R02, R01, R00 }, \
    		{ R15, R14, R13, R12, R11, R10 }, \
    		{ R25, R24, R23, R22, R21, R20 }, \
    		{ R35, R34, R33, R32, R31, R30 }, \
    		{ R45, R44, R43, R42, R41, R40 }, \
    		{ L00, L01, L02, L03, L04, L05 }, \
    		{ L10, L11, L12, L13, L14, L15 }, \
    		{ L20, L21, L22, L23, L24, L25 }, \
    		{ L30, L31, L32, L33, L34, L35 }, \
    		{ L40, L41, L42, L43, L44, L45 } \
    	}
#else
    #define KEYMAP( \
    	L00, L01, L02, L03, L04, L05, R00, R01, R02, R03, R04, R05, \
    	L10, L11, L12, L13, L14, L15, R10, R11, R12, R13, R14, R15, \
    	L20, L21, L22, L23, L24, L25, R20, R21, R22, R23, R24, R25, \
    	L30, L31, L32, L33, L34, L35, R30, R31, R32, R33, R34, R35, \
        L40, L41, L42, L43, L44, L45, R40, R41, R42, R43, R44, R45 \
    	) \
    	{ \
    		{ L00, L01, L02, L03, L04, L05 }, \
    		{ L10, L11, L12, L13, L14, L15 }, \
    		{ L20, L21, L22, L23, L24, L25 }, \
    		{ L30, L31, L32, L33, L34, L35 }, \
    		{ L40, L41, L42, L43, L44, L45 }, \
    		{ R00, R01, R02, R03, R04, R05 }, \
    		{ R10, R11, R12, R13, R14, R15 }, \
    		{ R20, R21, R22, R23, R24, R25 }, \
    		{ R30, R31, R32, R33, R34, R35 }, \
    		{ R40, R41, R42, R43, R44, R45 } \
    	}
#endif

#endif
