/* Copyright 2017 REPLACE_WITH_YOUR_NAME
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "woodpad.h"
#include "rgblight.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _NUMLOCK 0
#define _NAV 1
#define _ALT 2
#define _ADJUST 3

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_NUMLOCK] = KEYMAP( /* Base */
  MO(_ADJUST), KC_PSLS, KC_PAST, KC_PMNS,\
    KC_P7,  KC_P8, KC_P9, KC_PPLS,   \
    KC_P4,  KC_P5, KC_P6, KC_PEQL,   \
    KC_P1,  KC_P2, KC_P3, KC_COMMA,   \
    KC_LALT,  KC_P0, KC_PDOT, KC_PENT   \
),
[_ADJUST] = KEYMAP( /* Base */
  _______, _______, _______, RESET,\
    RGB_TOG,  RGB_MOD, _______, OUT_AUTO,   \
    RGB_HUI,  RGB_SAI, RGB_VAI, OUT_USB,   \
    RGB_HUD	,  RGB_SAD, RGB_VAD, OUT_BT,   \
    _______,  _______, _______, _______   \
)
};

const uint16_t PROGMEM fn_actions[] = {

};

void numlock_led_on(void) {
//  PORTF |= (1<<7);

 // rgblight_show_solid_color(0, 0, 0xFF);
}

void numlock_led_off(void) {
//  PORTF &= ~(1<<7);

//  rgblight_show_solid_color(0, 0xFF, 0);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//  switch (keycode) {
//	  case KC_NLCK:
//      if (!record->event.pressed) {
//		  if (!IS_LAYER_ON(_NAV)){
//			  numlock_led_off();
//			layer_on(_NAV);
//		  } else {
//			  numlock_led_on();
//			layer_off(_NAV);
//		  }
//	  }
//      return false;
//      break;
//	  case KC_LALT:
//      if (record->event.pressed) {
//		  layer_on(_ALT);
//	  } else {
//		  layer_off(_ALT);
//	  }
//	  // Allow normal processing of ALT?
//      return false;
//      break;
//  }
  return true;
}

void matrix_init_user(void) {
	rgblight_show_solid_color(0, 0xFF, 0);
  // set Numlock LED to output and low
//    DDRF |= (1<<7);
//    PORTF &= ~(1<<7);
//	numlock_led_on();
}

void matrix_scan_user(void) {

}


void led_set_user(uint8_t usb_led) {

}
