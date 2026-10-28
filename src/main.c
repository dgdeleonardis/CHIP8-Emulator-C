#include <stdio.h>

int main(int argc, char *argv[])
{
	int res = 0;
	if (argc > 1)
	{
		printf("%s\n", argv[1]);
	}
	else
	{
		printf("Usage: ./chip8 <ROM CHIP-8>\n");
		res = 1;
	}
	return res;
}
