CC = gcc
LD = gcc

CFLAGS = -Wall -Wextra -std=c99 -Iinclude -g
SFLAGS :=
LDFLAGS = -lm

TEST_SRC_FILES=$(wildcard src/test.c)
SRC_FILES=$(filter-out $(TEST_SRC_FILES) src/main.c, $(wildcard src/*.c))

OBJ_FILES=$(patsubst src/%.c,obj/%.o,$(SRC_FILES))
TEST_OBJ_FILES=$(patsubst src/%.c,obj/%.o,$(TEST_SRC_FILES))

all:game

game: $(OBJ_FILES) obj/main.o
	$(LD) $^ $(LDFLAGS) $(SFLAGS) -o $@

test: $(OBJ_FILES) $(TEST_OBJ_FILES) obj/test.o
	$(LD) $^ $(LDFLAGS) $(SFLAGS) -o $@

obj/%.o: src/%.c
	$(CC) -c $(CFLAGS) $(SFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f obj/*.o
	rm game