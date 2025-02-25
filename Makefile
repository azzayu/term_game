CC=gcc

all:game

game: main.o display.o

main.o: main.c display.h

display.o: display.c

clean:
	rm -f *~ *.o