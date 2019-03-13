#ifndef KEYBOARDS_GOLEM_LEFT_H_
#define KEYBOARDS_GOLEM_LEFT_H_

#include "golem.h"

#define LAYOUT( \
    L00, L01, L02, L03, L04, L05, L06, L07,    R00, R01, R02, R03, R04, R05, R06, R07, R37, \
    L10,   L11, L12, L13, L14, L15, L16,       R10, R11, R12, R13, R14, R15, R16, R17, R47, \
    L20,   L21, L22, L23, L24, L25, L26,       R20, R21, R22, R23, R24, R25, R26, R27, \
    L30,   L31, L32, L33, L34, L35, L36,       R30, R31, R32, R33, R34, R35, R36, \
                   L40, L41, L42, L43,         R40, R41, R42, R43, R44, R45, R46 \
) \
{ \
    { L00, L01, L02,   L03, L04, L05, L06, L07 }, \
    { L10, L11, KC_NO, L12, L13, L14, L15, L16 }, \
    { L20, L21, KC_NO, L22, L23, L24, L25, L26 }, \
    { L30, L31, KC_NO, L32, L33, L34, L35, L36 }, \
    { KC_NO, KC_NO, KC_NO, L40, L41, L42, L43, KC_NO }, \
    { R00, R01, R02, R03, R04, R05, R06, R07 }, \
    { R10, R11, R12, R13, R14, R15, R16, R17 }, \
    { R20, R21, R22, R23, R24, R25, R26, R27 }, \
    { R30, R31, R32, R33, R34, R35, R36, R37 }, \
    { R40, R41, R42, R43, R44, R45, R46, R47 } \
}



#endif /* KEYBOARDS_GOLEM_LEFT_H_ */
