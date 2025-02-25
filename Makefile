CC=gcc

all:game

game: main.o display.o player.o enemy.o

main.o: main.c display.h player.h enemy.h

player.o: player.c display.h

enemy.o: enemy.c player.h display.h

display.o: display.c

clean:
	rm -f *~ *.o