EXE=castle
CC=gcc
CFLAGS= -Wall -ansi -pedantic -I$(INCDIR)
TESTS = space_test object_test player_test set_test character_test link_test inventory_test interface_data_test

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

tests: $(TESTS)

space_test: $(OBJDIR)/space_test.o $(OBJDIR)/space.o $(OBJDIR)/set.o
	$(CC) $(CFLAGS) -o $@ $^ -lscreen -L$(LIBDIR)

object_test: $(OBJDIR)/object_test.o $(OBJDIR)/object.o
	$(CC) $(CFLAGS) -o $@ $^

player_test: $(OBJDIR)/player_test.o $(OBJDIR)/player.o $(OBJDIR)/inventory.o $(OBJDIR)/set.o
	$(CC) $(CFLAGS) -o $@ $^

set_test: $(OBJDIR)/set_test.o $(OBJDIR)/set.o
	$(CC) $(CFLAGS) -o $@ $^

character_test: $(OBJDIR)/character_test.o $(OBJDIR)/character.o
	$(CC) $(CFLAGS) -o $@ $^

link_test: $(OBJDIR)/link_test.o $(OBJDIR)/link.o
	$(CC) $(CFLAGS) -o $@ $^

inventory_test: $(OBJDIR)/inventory_test.o $(OBJDIR)/inventory.o $(OBJDIR)/set.o
	$(CC) $(CFLAGS) -o $@ $^

interface_data_test: $(OBJDIR)/interface_data_test.o $(OBJDIR)/interface_data.o $(OBJDIR)/command.o
	$(CC) $(CFLAGS) -o $@ $^

#############################################################################

clear:
	rm -rf $(OBJDIR)/*.o 

clean:
	rm -rf $(OBJDIR) $(EXE) *_test $(DOCDIR)

#############################################################################

run:
	@echo ">>>>>> Running castle"
	./castle castle.dat

runv:
	@echo ">>>>>> Running castle with valgrind"
	valgrind --leak-check=full ./castle castle.dat

run_log:
	@echo ">>>>>> Running castle with LOG and valgrind"
	valgrind --leak-check=full ./castle castle.dat -l output.log

run_deterministic:
	@echo ">>>>>> Running castle with deterministic seed and valgrind"
	valgrind --leak-check=full ./castle castle.dat -d

run_deterministic_with_log:
	@echo ">>>>>> Running castle with deterministic seed, LOG and valgrind"
	valgrind --leak-check=full ./castle castle.dat -l output.log -d

run_cmd:
	@echo ">>>>>> Running castle with cmd, LOG and valgrind"
	valgrind --leak-check=full ./castle castle.dat -l game1.log < game1.cmd

run_tests: $(TESTS)
	@echo ">>>>>> Running all tests"
	@for test in $(TESTS); do \
		echo "Running $$test"; \
		./$$test; \
	done

#############################################################################

.PHONY: all clear clean run runv run_log run_cmd tests run_tests

#############################################################################

doxygen:
	@echo ">>>>>> Executing Doxygen"
	doxygen Doxyfile