#include "bigswitch.h"
#include "print.h"

enum custom_keycodes {
  BL = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = KEYMAP(
    BL)
};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  return MACRO_NONE ;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_A:
    if (record->event.pressed) {
      SEND_STRING("This thing is BIG!!\n");
      return false;
    }
    break;
  case BL:
    if (record->event.pressed) {
      print("Stepping backlight\n");
      backlight_step();
      return false;
    }
    break;
  }
  return true;
}

void led_set_user(uint8_t usb_led) {

  if (usb_led & (1 << USB_LED_NUM_LOCK)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_COMPOSE)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_KANA)) {

  } else {

  }

}
