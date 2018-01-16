#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6071
#define DEVICE_VER      0x0001
#define MANUFACTURER    WoodKeys.click
#define PRODUCT         BigSeries Single Keyboard
#define DESCRIPTION     Single key board for Novelkeys Big Series Switch

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 1

/* key matrix pins */
#define MATRIX_ROW_PINS { B0 }
#define MATRIX_COL_PINS { B4 }
#define UNUSED_PINS

#define RGBLED_PINS { B1, B2, B3 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 50

/* key combination for command */
#define IS_COMMAND() ( \
    false \
)

/* prevent stuck modifiers */
#define PREVENT_STUCK_MODIFIERS

#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN D3
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 3
#endif

#ifdef BACKLIGHT_ENABLE
//#define BACKLIGHT_PIN B1
#define BACKLIGHT_LEVELS 5
#define BACKLIGHT_ON_STATE 1
#endif

#endif
