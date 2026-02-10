EXE=castle
CC=gcc
CFLAGS= -Wall -ansi -pedantic


$(EXE): command.o game_actions.o game_loop.o game_reader.o game.o graphic_engine.o object.o player.o space.o
	$(CC) $(CFLAGS) -o $@ $^ -lscreen -L.

command.o: command.c command.h types.h
	$(CC) $(CFLAGS) -c command.c 

game_actions.o: game_actions.c game_actions.h types.h command.h game.h
	$(CC) $(CFLAGS) -c game_actions.c 

game_loop.o: game_loop.c types.h command.h game.h game_reader.h graphic_engine.h game_actions.h
	$(CC) $(CFLAGS) -c game_loop.c 

game_reader.o: game_reader.c game_reader.h types.h space.h game.h
	$(CC) $(CFLAGS) -c game_reader.c 

game.o: game.c game.h types.h space.h command.h object.h player.h
	$(CC) $(CFLAGS) -c game.c 

graphic_engine.o: graphic_engine.c graphic_engine.h types.h space.h command.h game.h libscreen.h
	$(CC) $(CFLAGS) -c graphic_engine.c 

object.o: object.c object.h types.h
	$(CC) $(CFLAGS) -c object.c 

player.o: player.c player.h types.h
	$(CC) $(CFLAGS) -c player.c 

space.o: space.c space.h types.h
	$(CC) $(CFLAGS) -c space.c 

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EXE)

