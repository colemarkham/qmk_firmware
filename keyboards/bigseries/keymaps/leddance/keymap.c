#include "../../bigseries.h"
#include "print.h"

extern rgblight_config_t rgblight_config;

enum custom_keycodes {
  BL = SAFE_RANGE
};

enum custom_layers {
  BASE = 0,
  LED
};

//Tap Dance Declarations
enum {
  TD_TOGGLE = 0
};

void dance_toggle (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    println("Double tapped, switching layers");
    if (layer_state_is(LED)) {
      layer_off(LED);
    } else {
      layer_on(LED);
    }
  } else {
    print("Single tapped: ");
    if (layer_state_is(LED)) {
#ifdef RGBLIGHT_ENABLE
      if (!rgblight_config.enable) {
        rgblight_enable();
      }
      rgblight_step();
#endif
    } else {
      println("Base layer, sending string");
      SEND_STRING("This thing is BIG!!\n");
    }
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_TOGGLE]  = ACTION_TAP_DANCE_FN(dance_toggle)
// Other declarations would go here, separated by commas, if you have them
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = KEYMAP(
    TD(TD_TOGGLE)),
[LED] = KEYMAP(
    TD(TD_TOGGLE)
    )


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
