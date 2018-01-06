#include "bigswitch.h"
#include "print.h"

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

void update_leds(void);
uint8_t ledState = 0;

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
      ledState = (ledState + 1) % 8;
      xprintf("LED Layer, toggling value: %d\n", ledState);
      update_leds();
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


void set_led(uint8_t pin, uint8_t enable) {
  if (enable) {
    PORTB |= (1 << pin);
  } else {
    PORTB &= ~(1 << pin);
  }
}

void update_leds(void) {
  for (uint8_t idx = 0; idx < 3; idx++){
    set_led(idx+1, (ledState >> idx) & 1);
  }
}

void matrix_init_user(void) {
  /* set LED row pins to output and low */
  DDRB |= (1 << 1) | (1 << 2) | (1 << 3);
  PORTB &= ~(1 << 1) & ~(1 << 2) & ~(1 << 3);
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
      ledState = (ledState + 1) % 8;
      update_leds();
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
