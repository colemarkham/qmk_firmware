#include "../../bigseries.h"

//const uint8_t LED_PINS[] = RGBLED_PINS;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

KEYMAP(
    KC_A),


};


void update_leds(void);
uint8_t ledState = 0;
bool initialized = 0;

void set_led(uint8_t pin, uint8_t enable) {
  if (enable) {
    PORTB |= (1 << pin);
  } else {
    PORTB &= ~(1 << pin);
  }
}

void update_leds(void) {
  for (uint8_t idx = 0; idx < 3; idx++){
    set_led(idx+5, (ledState >> idx) & 1);
  }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  return MACRO_NONE ;
}

void matrix_init_user(void) {
  /* set LED row pins to output and low */
  DDRB |= (1 << 5) | (1 << 6) | (1 << 7);
  PORTB &= ~(1 << 5) & ~(1 << 6) & ~(1 << 7);
  if (!initialized){
//      debug_config.enable = true;
      dprintf("Initializing in matrix_scan_user");
      rgblight_enable();
      rgblight_mode(7);
      rgblight_sethsv(0,255,255);
      rgblight_setrgb(0x00, 0x00, 0xFF);
      ledState = 1;
      update_leds();
      initialized = 1;
    }
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_A:
    if (record->event.pressed) {
      ledState = (ledState + 1) % 8;
      xprintf("LED Layer, toggling value: %d\n", ledState);
      update_leds();
      SEND_STRING("Howdy!!\n");
      return false;
    }
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
