
src_files := src/*.c
all: clean chip8

chip8: $(src_files)
	gcc -Wall -Wextra -Werror -std=c99 src/main.c -o chip8

clean:
	rm -f chip8
