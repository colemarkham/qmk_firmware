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
#include "bunyan.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DEFAULT 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

#define XC_ADJ MO(_ADJUST)
#define XC_RSE MO(_RAISE)
#define XC_LWR MO(_LOWER)
#define XC_CTAL LCTL(KC_LALT)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#ifdef BLUETOOTH_ENABLE
#define OUT_BT_CUS OUT_BT
#else
#define OUT_BT_CUS KC_TRNS
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0]=KEYMAP(
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,      KC_KP_PLUS, KC_SLSH, KC_ASTR,        KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_BSLS,   KC_MINS,
		KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,      KC_KP_7,    KC_KP_8,    KC_KP_9,     KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPACE, KC_DEL,
		KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,      KC_KP_4,    KC_KP_5,    KC_KP_6,     KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,   KC_PGUP,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,      KC_KP_1,    KC_KP_2,    KC_KP_3,     KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,    KC_PGDN,
		XC_ADJ,  KC_LCTL, XC_CTAL, KC_LALT, XC_RSE, KC_LGUI,   KC_KP_0,    KC_DOT,     KC_ENT,      KC_SPC, XC_LWR, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,   KC_RALT ),

[_LOWER]=KEYMAP(
		_______, _______, _______, _______, _______, _______,   _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,   _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,   _______, _______, _______,          KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,   _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,   _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______),
[_RAISE]=KEYMAP(
		_______, _______, _______, _______, _______, _______,   _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,   _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,   _______, _______, _______,          KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,   _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______,   _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______),
[_ADJUST]=KEYMAP(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, RESET, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, OUT_AUTO, OUT_USB, OUT_BT_CUS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

};

const uint16_t PROGMEM fn_actions[] = {

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {

}


void led_set_user(uint8_t usb_led) {

}
