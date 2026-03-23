EXE=castle
CC=gcc
CFLAGS= -Wall -ansi -pedantic

all: $(EXE)

$(EXE): command.o game_actions.o game_loop.o game_reader.o game.o graphic_engine.o inventory.o object.o player.o space.o set.o character.o link.o
	$(CC) $(CFLAGS) -o $@ $^ -lscreen -L.

command.o: command.c command.h types.h
	$(CC) $(CFLAGS) -c command.c

game_actions.o: game_actions.c game_actions.h types.h command.h game.h
	$(CC) $(CFLAGS) -c game_actions.c

game_loop.o: game_loop.c types.h command.h game.h game_reader.h graphic_engine.h game_actions.h
	$(CC) $(CFLAGS) -c game_loop.c

game_reader.o: game_reader.c game_reader.h types.h space.h game.h object.h
	$(CC) $(CFLAGS) -c game_reader.c

game.o: game.c game.h types.h space.h command.h object.h player.h character.h
	$(CC) $(CFLAGS) -c game.c

graphic_engine.o: graphic_engine.c graphic_engine.h types.h space.h command.h game.h libscreen.h
	$(CC) $(CFLAGS) -c graphic_engine.c

inventory.o: inventory.c inventory.h types.h set.h
	$(CC) $(CFLAGS) -c inventory.c

link.o: link.c link.h types.h
	$(CC) $(CFLAGS) -c link.c

object.o: object.c object.h types.h
	$(CC) $(CFLAGS) -c object.c

player.o: player.c player.h types.h inventory.h
	$(CC) $(CFLAGS) -c player.c

space.o: space.c space.h types.h set.h
	$(CC) $(CFLAGS) -c space.c

set.o: set.c set.h types.h
	$(CC) $(CFLAGS) -c set.c

character.o: character.c character.h types.h
	$(CC) $(CFLAGS) -c character.c

space_test.o: space_test.c space_test.h space.h types.h
	$(CC) $(CFLAGS) -c space_test.c

space_test: space_test.o space.o set.o
	$(CC) $(CFLAGS) -o space_test space_test.o space.o set.o -lscreen -L.

test_space: space_test
	./space_test

character_test.o: character_test.c character_test.h character.h types.h
	$(CC) $(CFLAGS) -c character_test.c

character_test: character_test.o character.o
	$(CC) $(CFLAGS) -o character_test character_test.o character.o

test_character: character_test
	./character_test

set_test.o: set_test.c set_test.h set.h types.h
	$(CC) $(CFLAGS) -c set_test.c

set_test: set_test.o set.o
	$(CC) $(CFLAGS) -o set_test set_test.o set.o

test_set: set_test
	./set_test

player_test.o: player_test.c player_test.h player.h types.h
	$(CC) $(CFLAGS) -c player_test.c

player_test: player_test.o player.o
	$(CC) $(CFLAGS) -o player_test player_test.o player.o

test_player: player_test
	./player_test

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EXE) space_test character_test set_test

run:
	./castle castle.dat

runv:
	@echo ">>>>>> Running castle with valgrind"
	valgrind --leak-check=full ./castle castle.dat