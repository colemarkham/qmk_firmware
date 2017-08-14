#include "kingfisher.h"
#include "issi.h"
#include "lighting.h"
#include "action_layer.h"

//Define a shorter 'transparent' key code to make the keymaps more compact
// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = KEYMAP(\
  /* Keymap VANILLA: (Base Layer) Default Layer
   *   ,---------------------------------------------------------------------.
   *   |ESC |  Q |  W |  E |  R |  T |  Y |  U |  I |  O |  P |   [|   ]|   \|
   *   |---------------------------------------------------------------------|
   *   |Tab  |  A |  S |  D |  F |  G |  H |  J |  K |  L |   ;|   '| RETURN|
   *   |---------------------------------------------------------------------| 
   *   |SHIFT   |   Z|   X|   C|   V|   B|   N|   M|   ,|   .|   /|SHIFT |END|
   *   |---------------------------------------------------------------------|
   *    |ADJUST|CTRL||ALT|   WIN    |RAISE|    SPACE   ||LEFT|UP|DOWN|RIGHT|
   *    `-------------------------------------------------------------------'  
   */
		KC_FN1, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC,\
   KC_TAB,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,  KC_BSLASH , KC_ENT,\
   KC_LSFT,  KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT, \
   MO(_ADJUST), KC_LCTL, KC_LALT, KC_LGUI, KC_SPACE, MO(_RAISE), XXXXXXX, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT),
   [_RAISE] = KEYMAP(\

		   KC_TILD, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_LPRN, KC_RPRN, _______,\
		   _______,  _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL, _______, _______, _______,   _______, _______,\
		   KC_CAPS,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  		   _______, _______, _______, _______, _______, _______, XXXXXXX, _______, _______, _______, _______),

   [_ADJUST] = KEYMAP(\

		   BL_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_DEL,\
		   BL_DEC,  BL_INC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______,\
		   _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
		   _______, _______, _______, _______, _______, _______, XXXXXXX, _______, _______, _______, RESET)
};

const uint16_t PROGMEM fn_actions[] = {
    ACTION_FUNCTION(LFK_CLEAR),                               // FN0 - reset layers
    ACTION_FUNCTION(LFK_ESC_TILDE),                           // FN1 - esc+shift = ~, else escape
  };


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
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
	set_backlight_by_keymap(0, 2);
}

