#include "bigswitch.h"

void matrix_scan_kb(void) {
  // Looping keyboard code goes here
  // This runs every cycle (a lot)
  matrix_scan_user();
#ifdef BACKLIGHT_ENABLE
  backlight_task();
#endif
};
