CC=gcc

all:game

game: main.o display.o player.o enemy.o
	gcc main.o display.o player.o enemy.o -o game

main.o: main.c enemy.h

player.o: player.c display.h

enemy.o: enemy.c player.h 

display.o: display.c

clean:
	rm -f *.o
	rm game