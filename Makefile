CC = gcc
LD = gcc

CFLAGS = -Wall -Wextra -std=c99 -Iinclude -g
SFLAGS :=
LDFLAGS = -lm

SRC_FILES=$(wildcard src/*.c)

OBJ_FILES=$(patsubst src/%.c,obj/%.o,$(SRC_FILES))

all:game

game: $(OBJ_FILES) obj/main.o
	$(LD) $^ $(LDFLAGS) $(SFLAGS) -o $@

obj/%.o: src/%.c
	$(CC) -c $(CFLAGS) $(SFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f obj/*.o
	rm game