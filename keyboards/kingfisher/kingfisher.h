#ifndef KINGFISHER_H
#define KINGFISHER_H

/* if the kb.h file exists (because we're running from qmkbuilder) include it */
#ifdef __has_include
#if __has_include("kb.h")
#include "kb.h"
#endif
#endif

#include "quantum.h"
#include "matrix.h"
#include <avr/sfr_defs.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif



enum action_functions {
    LFK_CLEAR = 0,          // Resets all layers
    LFK_ESC_TILDE,          // esc+lshift = ~
    LFK_LED_TEST,          // Test LEDs
};

void reset_keyboard_kb(void);

#ifndef KEYMAP
/* RevC/D Keymap */
// This a shortcut to help you visually see your layout.
/*
* ,---------.  ,-----------------------------------------------------------------------.  ,---------
* | 11 | 12 |  | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 1A | 1B | 1C | 1D | 1E | 1F |   1G |  | 1H | 1I |
* |---------|  |-----------------------------------------------------------------------|  |---------|
* | 21 | 22 |  | 23  | 24 | 25 | 26 | 27 | 28 | 29 | 2A | 2B | 2C | 2D | 2E | 2F |  2G |  | 2H | 2I |
* |---------|  |-----------------------------------------------------------------------|  `---------'
* | 31 | 32 |  | 33    | 34 | 35 | 36 | 37 | 38 | 39 | 3A | 3B | 3C | 3D | 3E |     3F |
* |---------|  |-----------------------------------------------------------------------|  ,----.
* | 41 | 42 |  | 43      | 45 | 46 | 47 | 48 | 49 | 4A | 4B | 4C | 4D | 4E |        4F |  | 4H |
* |---------|  |-------------------------------------------------------------------------------------.
* | 51 | 52 |  | 53  | 54  | 55 |               59                |  5D |  5E |  5F | | 5G | 5H | 5I |
* `---------'  `--------------------------------------------------------------------' `--------------'
*/
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define KEYMAP( \
    k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, \
    k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, \
    k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C,\
    k41, k42, k43, k44,      k45,      k46, k47, k48 ,k49, k4B, k4C \
) \
{ \
    {k11, k12, k13, k14, k15,   k16, k17,   k18, k19, k1A, k1B, k1C, k1D,   k1E}, \
    {k21, k22, k23, k24, k25,   k26, k27,   k28, k29, k2A, k2B, k2C, k2D,   k2E}, \
    {k31, k32, k33, k34, k35,   k36, k37,   k38, k39, k3A, k3B, k3C, KC_NO, KC_NO}, \
    {k41, k42, k43, k44, KC_NO, k45, KC_NO, k46, k47, k48 ,k49, k4B, k4C,   KC_NO}, \
}
#endif //!KEYMAP

#endif //KINGFISHER_H
