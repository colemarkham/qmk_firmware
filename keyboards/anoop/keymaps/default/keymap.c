#include "anoop.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP( /* Base */
    KC_DEL, KC_BSPC, KC__MUTE, KC_ESC, \
    KC_KP_ASTERISK, KC_KP_SLASH, KC__VOLUP, KC__VOLDOWN, \
    KC_KP_MINUS, KC_P9, KC_P8, KC_P7, \
    KC_KP_PLUS, KC_P6, KC_P5, KC_P4, \
         KC_P3, KC_P2, KC_P1, \
    KC_KP_ENTER, KC_KP_DOT, KC_P0, KC_TAB \
),
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
