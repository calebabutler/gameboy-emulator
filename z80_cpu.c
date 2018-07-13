
#include <stdint.h>
#include <stdio.h>

#include "z80_cpu.h"

void z80_nop(struct Z80CPU *const cpu)
{
	cpu->reg.m = 1;
	cpu->reg.t = 4;
}

void z80_inc_2r(struct Z80CPU *const cpu, uint8_t *const reg1,
	uint8_t *const reg2)
{
	(*reg2)++;
	if ((*reg2) == 0) {
		(*reg1)++;
	}
	cpu->reg.m = 1;
	cpu->reg.t = 8;
}

void z80_inc_r(struct Z80CPU *const cpu, uint8_t *const reg)
{
	(*reg)++;
	cpu->reg.f &= ~(0x20 | 0x40 | 0x80);
	if ((*reg) == 0) {
		cpu->reg.f |= 0x80;
	}
	if (((*reg) & 15) == 0) {
		cpu->reg.f |= 0x20;
	}
	cpu->reg.m = 1;
	cpu->reg.t = 4;
}

void z80_dec_r(struct Z80CPU *const cpu, uint8_t *const reg)
{
	(*reg)--;
	cpu->reg.f |= 0x40;
	cpu->reg.f &= ~(0x20 | 0x80);
	if (((*reg) & 15) == 15) {
		cpu->reg.f |= 0x20;
	}
	if ((*reg) == 0) {
		cpu->reg.f |= 0x80;
	}
	cpu->reg.m = 1;
	cpu->reg.t = 4;
}

void z80_rlc_a(struct Z80CPU *const cpu)
{
	const uint8_t i = cpu->reg.a >> (8 - 1);
	cpu->reg.a <<= 1;
	cpu->reg.a |= i;
	cpu->reg.f = 0;
	if (i == 1) {
		cpu->reg.f |= 0x10;
	}
	cpu->reg.m = 1;
	cpu->reg.t = 4;
}

void z80_dec_2r(struct Z80CPU *const cpu, uint8_t *const reg1,
	uint8_t *const reg2)
{
	(*reg2)--;
	if ((*reg2) == 255) {
		(*reg1)--;
	}
	cpu->reg.m = 1;
	cpu->reg.t = 8;
}

void z80_rrc_a(struct Z80CPU *const cpu)
{
	const uint8_t i = cpu->reg.a << (8 - 1);
	cpu->reg.a >>= 1;
	cpu->reg.a |= i;
	cpu->reg.f = 0;
	if (i == 1) {
		cpu->reg.f |= 0x10;
	}
	cpu->reg.m = 1;
	cpu->reg.t = 4;
}

void z80_rl_a(struct Z80CPU *const cpu)
{
	const uint8_t i = cpu->reg.a >> (8 - 1);
	cpu->reg.a <<= 1;
	if ((cpu->reg.f & 0x10) == 0x10) {
		cpu->reg.a |= 1;
	}
	cpu->reg.f = 0;
	if (i == 1) {
		cpu->reg.f |= 0x10;
	}
	cpu->reg.m = 1;
	cpu->reg.t = 4;
}

void z80_rr_a(struct Z80CPU *const cpu)
{
	const uint8_t i = cpu->reg.a << (8 - 1);
	cpu->reg.a >>= 1;
	if ((cpu->reg.f & 0x10) == 0x10) {
		cpu->reg.a |= 128;
	}
	cpu->reg.f = 0;
	if (i == 128) {
		cpu->reg.f |= 0x10;
	}
	cpu->reg.m = 1;
	cpu->reg.t = 4;
}

void z80_da_a(struct Z80CPU *const cpu)
{
	const uint8_t high_nibble = cpu->reg.a >> 4;
	const uint8_t low_nibble = cpu->reg.a & 15;
	if ((cpu->reg.f & 0x40) == 0x40) {
		if ((cpu->reg.f & 0x10) ==  0x10) {
			if ((high_nibble >= 7) &&
			    (high_nibble <= 0x0F) &&
			    ((cpu->reg.f & 0x20) == 0) &&
			    (low_nibble >= 0) &&
			    (low_nibble <= 9)) {
				cpu->reg.a += 0xA0;
				cpu->reg.f |= 0x10;
			} else if ((high_nibble >= 6) &&
				   (high_nibble <= 0x0F) &&
				   ((cpu->reg.f & 0x20) == 0x20) &&
				   (low_nibble >= 6) &&
				   (low_nibble <= 0x0F)) {
				cpu->reg.a += 0x9A;
				cpu->reg.f |= 0x10;
			}
		} else {
			if ((high_nibble >= 0) &&
			    (high_nibble <= 8) &&
			    ((cpu->reg.f & 0x20) == 0x20) &&
			    (low_nibble >= 6) &&
			    (low_nibble <= 0x0F)) {
				cpu->reg.a += 0xFA;
				cpu->reg.f &= ~(0x10);
			}
		}
	} else {
		if ((cpu->reg.f & 0x10) == 0x10) {
			if ((high_nibble >= 0) &&
			    (high_nibble <= 2) &&
			    ((cpu->reg.f & 0x20) == 0) &&
			    (low_nibble >= 0) &&
			    (low_nibble <= 9)) {
				cpu->reg.a += 0x60;
				cpu->reg.f |= 0x10;
			} else if ((high_nibble >= 0) &&
				   (high_nibble <= 2) &&
				   ((cpu->reg.f & 0x20) == 0) &&
				   (low_nibble >= 0x0A) &&
				   (low_nibble <= 0x0F)) {
				cpu->reg.a += 0x66;
				cpu->reg.f |= 0x10;
			} else if ((high_nibble >= 0) &&
				   (high_nibble <= 3) &&
				   ((cpu->reg.f & 0x20) == 0x20) &&
				   (low_nibble >= 0) &&
				   (low_nibble <= 3)) {
				cpu->reg.a += 0x66;
				cpu->reg.f |= 0x10;
			}
		} else {
			if ((high_nibble >= 0) &&
			    (high_nibble <= 8) &&
			    ((cpu->reg.f & 0x20) == 0) &&
			    (low_nibble >= 0x0A) &&
			    (low_nibble <= 0x0F)) {
				cpu->reg.a += 0x06;
				cpu->reg.f &= ~(0x10);
			} else if ((high_nibble >= 0) &&
				   (high_nibble <= 9) &&
				   ((cpu->reg.f & 0x20) == 0x20) &&
				   (low_nibble >= 0) &&
				   (low_nibble <= 3)) {
				cpu->reg.a += 0x06;
				cpu->reg.f &= ~(0x10);
			} else if ((high_nibble >= 0x0A) &&
				   (high_nibble <= 0x0F) &&
				   ((cpu->reg.f & 0x20) == 0) &&
				   (low_nibble >= 0) &&
				   (low_nibble <= 9)) {
				cpu->reg.a += 0x60;
				cpu->reg.f |= 0x10;
			} else if ((high_nibble >= 9) &&
				   (high_nibble <= 0x0F) &&
				   ((cpu->reg.f & 0x20) == 0) &&
				   (low_nibble >= 0x0A) &&
				   (low_nibble <= 0x0F)) {
				cpu->reg.a += 0x66;
				cpu->reg.f |= 0x10;
			} else if ((high_nibble >= 0x0A) &&
				   (high_nibble <= 0x0F) &&
				   ((cpu->reg.f & 0x20) == 0x20) &&
				   (low_nibble >= 0) &&
				   (low_nibble <= 3)) {
				cpu->reg.a += 0x66;
				cpu->reg.f |= 0x10;
			}
		}
	}
	if (cpu->reg.a == 0) {
		cpu->reg.f |= 0x80;
	} else {
		cpu->reg.f &= ~(0x80);
	}
	cpu->reg.f &= ~(0x20);
	cpu->reg.m = 1;
	cpu->reg.t = 4;
}

int main(int argc, char *argv[])
{
	struct Z80CPU cpu;
	// set variables
	cpu.reg.a = 0; cpu.reg.b = 0; cpu.reg.c = 0; cpu.reg.d = 0;
	cpu.reg.e = 0; cpu.reg.h = 0; cpu.reg.l = 0;
	cpu.reg.f = 0;
	cpu.reg.m = 0; cpu.reg.t = 0;
	cpu.reg.pc = 0;
	cpu.reg.sp = 0;

	// print results
	printf("a = %d; b = %d; c = %d; d = %d\n",
		cpu.reg.a, cpu.reg.b, cpu.reg.c, cpu.reg.d);
	printf("e = %d; h = %d; l = %d\n",
		cpu.reg.e, cpu.reg.h, cpu.reg.l);
	printf("f = %#02x\n", cpu.reg.f);
	printf("m = %d; t = %d\n", cpu.reg.m, cpu.reg.t);
	printf("pc = %d\n", cpu.reg.pc);
	printf("sp = %d\n", cpu.reg.sp);
}

// vi: set ts=8 sts=8 noet sw=8 tw=80:
