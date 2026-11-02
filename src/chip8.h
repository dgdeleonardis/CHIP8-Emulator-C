#ifndef CHIP8_H
#define CHIP8_H
/* #pragma once */


#define CHIP8_WIDTH (64)
#define CHIP8_HEIGHT (32)

typedef struct
{
	/* state var: 1 is running, 0 is not running */
	unsigned char running;
	
	/* last opcode read */
	unsigned char opcode;

	/*
	 * 4k memory:
	 * - 0x000 - 0x1FF interpreter (font area)
	 * - 0x050 - 0x0A0 4x5 font of hex digits 0-F
	 * - 0x200 - 0xFFF program and working area
	 */
	unsigned char memory[4096];

	/* 16 general purpose 8 bit registers: V0 ... VF */
	unsigned char V[16];

	/* index register */
	unsigned short I;

	/* pc (program counter) register */
	unsigned short pc;

	/*
	 * screen monochrome: 
	 * - 1 byte per pixel: 0 off, 1 on 
	 * - pixel (x,y)-> screen[x + (CHIP8_SCREEN_WIDTH * y)]
	 */
	unsigned char gfx[CHIP8_WIDTH * CHIP8_HEIGHT];
	
	/* 
         * raised by the opcodes that touch the screen: tells there is
	 * something new to show.
	 */
	unsigned char draw;

	/* timers */
	unsigned char delay_timer;
	unsigned char sound_timer;

	/* call stack */
	unsigned short stack[16];

	/* stack pointer of idx of the first free one */
	unsigned short sp;

	/* keyboard: 0 not pressed, 1 pressed */
	unsigned char key[16];
} Chip8;

/**
 * chip8Init - create and initialize chip8 instance
 *
 * Return: pointer to chip8 struct. 
 */
Chip8* chip8Init(void);

/**
 * chip8Destroy - destroy a chip8 instance
 * @chip: pointer to chip8 instance, may be NULL
 */
void chip8Destroy(Chip8* chip);

#endif /* CHIP8_H */
