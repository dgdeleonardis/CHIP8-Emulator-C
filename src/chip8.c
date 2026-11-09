#include "chip8.h"
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define CHIP8_MEMORY_MAP_PROGRAM_START_ADDRESS (0x200u)

#define FETCH_OPCODE(chip8) \
	(chip8->memory[chip8->pc + 0] << 8) | (chip8->memory[chip8->pc + 1])

/* font */
static const unsigned char CHIP8_FONTSET[80] = {
  0xF0, 0x90, 0x90, 0x90, 0xF0, /* 0 */
  0x20, 0x60, 0x20, 0x20, 0x70, /* 1 */
  0xF0, 0x10, 0xF0, 0x80, 0xF0, /* 2 */
  0xF0, 0x10, 0xF0, 0x10, 0xF0, /* 3 */
  0x90, 0x90, 0xF0, 0x10, 0x10, /* 4 */
  0xF0, 0x80, 0xF0, 0x10, 0xF0, /* 5 */
  0xF0, 0x80, 0xF0, 0x90, 0xF0, /* 6 */
  0xF0, 0x10, 0x20, 0x40, 0x40, /* 7 */
  0xF0, 0x90, 0xF0, 0x90, 0xF0, /* 8 */
  0xF0, 0x90, 0xF0, 0x10, 0xF0, /* 9 */
  0xF0, 0x90, 0xF0, 0x90, 0x90, /* A */
  0xE0, 0x90, 0xE0, 0x90, 0xE0, /* B */
  0xF0, 0x80, 0x80, 0x80, 0xF0, /* C */
  0xE0, 0x90, 0x90, 0x90, 0xE0, /* D */
  0xF0, 0x80, 0xF0, 0x80, 0xF0, /* E */
  0xF0, 0x80, 0xF0, 0x80, 0x80  /* F */
};

Chip8* chip8Init(void)
{
	Chip8* chip = calloc(1, sizeof(Chip8));
	if (chip == NULL)
	{
		printf("[ERROR] - Machine allocation failed\n");
	}
	else if (memcpy((void *) chip->memory, (void *) CHIP8_FONTSET, 80) == 0)
	{
		printf("[ERROR] - Font loading failed\n");
	}
	else
	{
		chip->pc = 0x200;
		chip->running = 1;
		printf("[INFO] - Machine allocated at %p\n", (void *) chip);
	}
	
	return chip;
}

void chip8Destroy(Chip8 *chip)
{
	if (chip != NULL)
	{
		memset(chip, 0, sizeof(Chip8));
		free(chip);
		printf("[INFO] - Machine destroyed\n");
	}
}

void chip8LoadProgram(Chip8* chip, char *program)
{
	size_t n = 0;
	size_t max = 4096 - CHIP8_MEMORY_MAP_PROGRAM_START_ADDRESS;
	
	/* open program with rb option (binary file) */
	FILE *fp = fopen(program, "rb");
	if (fp == NULL)
	{
		printf("[ERROR] - Cannot open '%s'\n", program);
		exit(1);
	}
	
	n = fread(chip->memory + CHIP8_MEMORY_MAP_PROGRAM_START_ADDRESS, 1, max, fp);
	
	if (ferror(fp) != 0)
	{
		printf("[ERROR] - Read error on '%s'\n", program);
		fclose(fp);
		exit(1);
	}

	if (n == 0)
	{
		printf("[ERROR] - ROM '%s' empty\n", program);
		fclose(fp);
                exit(1);
	}

	if (fgetc(fp) != EOF)
	{
		printf("[ERROR] - ROM '%s' too big\n", program);
		fclose(fp);
		exit(1);
	}

	printf("[INFO] - ROM loaded at %.3x (first byte: 0x%x)\n", 
		CHIP8_MEMORY_MAP_PROGRAM_START_ADDRESS, 
		chip->memory[CHIP8_MEMORY_MAP_PROGRAM_START_ADDRESS]);
	fclose(fp);
	return;
}

void chip8Step(Chip8 * chip)
{
	if (chip->pc >= 4096)
	{
		printf("[INFO] - pc = 0x%.3x: out of memory\n", chip->pc);
		exit(0);
	}

	chip->opcode = FETCH_OPCODE(chip);
	chip->pc = chip->pc + 0x2;
}
