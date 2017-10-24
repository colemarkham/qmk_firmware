/*
Copyright 2017 REPLACE_WITH_YOUR_NAME

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6069
#define MANUFACTURER    WoodKeys.click
#define PRODUCT         woodpad
#define DESCRIPTION     Basic numpad

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

#ifdef SUBPROJECT_rev1
    #include "rev1/config.h"
#endif
#ifdef SUBPROJECT_rev2_promicro
    #include "rev2_promicro/config.h"
#endif
#ifdef SUBPROJECT_rev2_featherble
    #include "rev2_featherble/config.h"
#endif

/* key combination for command */
#define IS_COMMAND() ( \
    false \
)

#endif
