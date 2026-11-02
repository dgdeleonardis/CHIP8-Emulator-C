CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
SRC = src/main.c src/chip8.c
BIN = chip8

all: clean build

build: $(SRC)
	$(CC)  $(CFLAGS) $(SRC) -o $(BIN)

clean:
	rm -f $(BIN)
