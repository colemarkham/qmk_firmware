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

#ifndef REV2_FEATHERBLE_CONFIG_H
#define REV2_FEATHERBLE_CONFIG_H

// AdafruitBLE needs this, not sure why it isn't included by default
#include <avr/pgmspace.h>

/* USB Device descriptor parameter */
#define DEVICE_VER      0x0002

#define MATRIX_ROW_PINS { F1, D6, F0, B7, D2 }
#define MATRIX_COL_PINS { F7, F6, F5, F4 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL, or CUSTOM_MATRIX */
#define DIODE_DIRECTION COL2ROW

#define CATERINA_BOOTLOADER
 
/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCING_DELAY 5


#endif
