EXE=castle
CC=gcc
CFLAGS= -Wall -ansi -pedantic -I$(INCDIR)

SRCDIR = ./src
INCDIR = ./include
OBJDIR = ./obj
LIBDIR = ./lib
DOCDIR = ./doc

OBJS = $(OBJDIR)/command.o $(OBJDIR)/game_actions.o $(OBJDIR)/game_loop.o \
       $(OBJDIR)/game_reader.o $(OBJDIR)/game.o $(OBJDIR)/graphic_engine.o \
       $(OBJDIR)/inventory.o $(OBJDIR)/object.o $(OBJDIR)/player.o \
       $(OBJDIR)/space.o $(OBJDIR)/set.o $(OBJDIR)/character.o \
       $(OBJDIR)/link.o $(OBJDIR)/interface_data.o

#############################################################################

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lscreen -L$(LIBDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

#############################################################################

space_test: $(OBJDIR)/space_test.o $(OBJDIR)/space.o $(OBJDIR)/set.o
	$(CC) $(CFLAGS) -o $@ $^ -lscreen -L.

test_space: space_test
	./space_test

object_test: $(OBJDIR)/object_test.o $(OBJDIR)/object.o
	$(CC) $(CFLAGS) -o $@ $^

test_object: object_test
	./object_test

player_test: $(OBJDIR)/player_test.o $(OBJDIR)/player.o $(OBJDIR)/inventory.o $(OBJDIR)/set.o
	$(CC) $(CFLAGS) -o $@ $^

test_player: player_test
	./player_test

set_test: $(OBJDIR)/set_test.o $(OBJDIR)/set.o
	$(CC) $(CFLAGS) -o $@ $^

test_set: set_test
	./set_test

character_test: $(OBJDIR)/character_test.o $(OBJDIR)/character.o
	$(CC) $(CFLAGS) -o $@ $^

test_character: character_test
	./character_test

link_test: $(OBJDIR)/link_test.o $(OBJDIR)/link.o
	$(CC) $(CFLAGS) -o $@ $^

test_link: link_test
	./link_test

inventory_test: $(OBJDIR)/inventory_test.o $(OBJDIR)/inventory.o $(OBJDIR)/set.o
	$(CC) $(CFLAGS) -o $@ $^

test_inventory: inventory_test
	./inventory_test

interface_data_test: $(OBJDIR)/interface_data_test.o $(OBJDIR)/interface_data.o $(OBJDIR)/command.o
	$(CC) $(CFLAGS) -o $@ $^

test_interface_data: interface_data_test
	./interface_data_test

#############################################################################

clear:
	rm -rf $(OBJDIR)/*.o 

clean:
	rm -rf $(OBJDIR) $(EXE) *_test $(DOCDIR)

#############################################################################

run:
	./castle castle.dat

runv:
	@echo ">>>>>> Running castle with valgrind"
	valgrind --leak-check=full ./castle castle.dat

#############################################################################

doxygen:
	@echo ">>>>>> Executing Doxygen"
	doxygen Doxyfile