#ifndef EH1_H
#define EH1_H

#include "../lets_macro.h"

//void promicro_bootloader_jmp(bool program);
#include "quantum.h"

//void promicro_bootloader_jmp(bool program);

#define KEYMAP( \
	k01, k02, k03, k04, k05, k06, \
	k11, k12, k13, k14, k15, k16, \
	k21, k22, k23, k24, k25, k26, \
	k31, k32, k33, k34, k35, k36  \
	) \
	{ \
		{ k01, k02, k03, k04, k05, k06 }, \
		{ k11, k12, k13, k14, k15, k16 }, \
		{ k21, k22, k23, k24, k25, k26 }, \
		{ k31, k32, k33, k34, k35, k36 }  \
	}

#endif