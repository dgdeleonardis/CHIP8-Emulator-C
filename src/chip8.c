#include "chip8.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CHIP8_MEMORY_MAP_PROGRAM_START_ADDRESS (0x200u)

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
	FILE *fp = fopen(program, "r");
	if (fp == NULL)
	{
		printf("[ERROR] - Cannot open '%s'\n", program);
		exit(1);
	}
	else
	{
		int c = 0;
		unsigned memp = CHIP8_MEMORY_MAP_PROGRAM_START_ADDRESS;
		/* standard C I/O file reading loop */
		while ((c = fgetc(fp)) != EOF)
		{
			if (memp >= 0xFFF)
			{
				printf("[ERROR] - ROM '%s' too big\n", program);
				exit(1);
			}

			chip->memory[memp] = (unsigned char) c;
			memp++;
		}
		
		if ((c == EOF) && (memp == CHIP8_MEMORY_MAP_PROGRAM_START_ADDRESS))
		{
			printf("[ERROR] - ROM '%s' empty\n", program);
			exit(1);
		}

		printf("[INFO] - ROM loaded at %.3x (first byte: 0x00)\n", CHIP8_MEMORY_MAP_PROGRAM_START_ADDRESS);
	}
	return;
}
