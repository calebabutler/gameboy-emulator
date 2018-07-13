
#ifndef _GAMEBOY_Z80_CPU_H
#define _GAMEBOY_Z80_CPU_H

#include <stdint.h>

struct Z80CPU {
	struct {
		uint8_t m, t;
	} clock;
	// registers
	struct {
		// basic 1 byte registers
		uint8_t a, b, c, d, e, h, l;
		// flag register. four flags:
		//	zero (0x80) - set if the last operation produced a zero
		//	subtraction (0x40) - set if the last operation was
		//		subtraction
		//	half-carry (0x20) - set if, in the result of the last
		//		operation, the lower half of the byte
		//		overflowed past 15
		//	carry (0x10) - set if the last operation produced a
		//		result over 255 or under 0
		uint8_t f;
		// clock for last instruction
		uint8_t m, t;
		// program counter
		uint16_t pc;
		// stack pointer register (for basic stack support)
		uint16_t sp;
	} reg;
};

#endif // _GAMEBOY_Z80_CPU_H

// vi: set ts=8 sts=8 noet sw=8 tw=80:
