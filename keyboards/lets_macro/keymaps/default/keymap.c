// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

// Default ECO Layout
// KLE here : http://www.keyboard-layout-editor.com/#/gists/0733eca6b4cb88ff9d7de746803f4039

#include "lets_macro.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _FN1 2
#define _FN2 3

enum eco_keycodes {
  QWERTY = SAFE_RANGE
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |
 * |------+------+------+------+------+------|
 * | FN1  |   A  |   S  |   D  |   F  |   G  |
 * |------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |
 * |------+------+------+------+------+------|
 * | Ctrl |  GUI | Alt  | Del  | SPC  | FN2  |
 * `-----------------------------------------'
 */
[_QWERTY] = KEYMAP(
  KC_ESC,  KC_Q,   KC_W,    KC_E,   KC_R,     KC_T,     
  KC_1,  KC_A,   KC_S,    KC_D,   KC_F,     KC_G,
  KC_LSFT, KC_Z,   KC_X,    KC_C,   KC_V,     KC_B,    
  KC_LCTL, KC_LGUI,KC_LALT, KC_DEL, KC_SPC, KC_2
),

/* FN1
 * ,-----------------------------------------.
 * |caltde|   !  |   @  |   #  |   $  |   %  |
 * |------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |
 * |------+------+------+------+------+------|
 * |      |      |      |      |      |      |
 * |------+------+------+------+------+------|
 * |RESET |      |      |      |      |      |
 * `-----------------------------------------'
 */
[_FN1] = KEYMAP(
  CALTDEL, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  
  _______, _______, _______, _______, _______, _______,
  RESET,   _______, _______, _______, _______, _______
),

/* Raise
 * ,-----------------------------------------.
 * |RESET |   1  |   2  |   3  |   4  |   5  |
 * |------+------+------+------+------+------|
 * |Taskmg|  F1  |  F2  |  F3  |  F4  |  F5  |
 * |------+------+------+------+------+------|
 * |      |      |      |      |      |      |
 * |------+------+------+------+------+------|
 * |      |      |      |      |      |      |
 * `-----------------------------------------'
 */
[_FN2] = KEYMAP(
  RESET , KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   
  TSKMGR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  
  _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______
)

};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
  }
  return true;
}

