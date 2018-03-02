#include "bigswitch.h"
#include "print.h"

extern rgblight_config_t rgblight_config;

bool initialized = 0;

enum custom_keycodes {
  BL = SAFE_RANGE
};

void update_leds(void);
uint8_t ledState = 0;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = KEYMAP(
    BL
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
//  rgblight_setrgb((ledState >> 2) & 0xFF, (ledState >> 1) & 0xFF, ledState & 0xFF);
}

void matrix_init_user(void) {
  /* set LED row pins to output and low */
  DDRB |= (1 << 1) | (1 << 2) | (1 << 3);
  PORTB &= ~(1 << 1) & ~(1 << 2) & ~(1 << 3);
}

void matrix_scan_user(void) {
  if (!initialized){
    debug_config.enable = true;
    dprintf("Initializing in matrix_scan_user");
    rgblight_enable();
    rgblight_mode(1);
    rgblight_sethsv(0,255,255);
    rgblight_setrgb(0x00, 0x00, 0xFF);
    initialized = 1;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case BL:
    if (record->event.pressed) {

#ifdef RGBLIGHT_ENABLE
      if (!rgblight_config.enable) {
        rgblight_enable();
      }
      rgblight_step();
      if (rgblight_config.hue == 511){
        rgblight_sethsv(0,255,255);
      }
#endif
      ledState = (ledState + 1) % 8;
      xprintf("LED Layer, toggling value: %d\n", ledState);
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
