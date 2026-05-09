EXE=castle
CC=gcc
CFLAGS= -Wall -ansi -pedantic -I$(INCDIR)
TESTS = space_test object_test player_test set_test character_test link_test inventory_test interface_data_test

SRCDIR = ./src
INCDIR = ./include
OBJDIR = ./obj
LIBDIR = ./lib
DOCDIR = ./doc
TESTDIR = ./test
CMDDIR = ./cmd
TXTDIR = ./txt
LOGDIR = ./log

OBJS = $(OBJDIR)/command.o $(OBJDIR)/game_actions.o $(OBJDIR)/game_loop.o \
       $(OBJDIR)/game_reader.o $(OBJDIR)/game.o $(OBJDIR)/graphic_engine.o \
       $(OBJDIR)/inventory.o $(OBJDIR)/object.o $(OBJDIR)/player.o \
       $(OBJDIR)/space.o $(OBJDIR)/set.o $(OBJDIR)/character.o \
       $(OBJDIR)/link.o $(OBJDIR)/interface_data.o $(OBJDIR)/game_rules.o

#############################################################################

all: dirs $(EXE)

dirs:
	@mkdir -p $(OBJDIR) $(CMDDIR) $(TXTDIR) $(LOGDIR)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lscreen -L$(LIBDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

#############################################################################
# TESTS

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
# CLEAN

clear:
	rm -rf $(OBJDIR)/*.o 

clean:
	rm -rf $(OBJDIR) $(EXE) $(TESTDIR) $(DOCDIR) $(LOGDIR)

#############################################################################
# RUN 1 PLAYER

run1:
	@echo ">>>>>> Running castle"
	./castle castle1p.dat

runv1:
	@echo ">>>>>> Running castle with valgrind"
	valgrind --leak-check=full ./castle castle1p.dat

run_log1:
	@echo ">>>>>> Running castle with LOG and valgrind"
	valgrind --leak-check=full ./castle castle1p.dat -l output.log

run_deterministic1:
	@echo ">>>>>> Running castle with deterministic seed and valgrind"
	valgrind --leak-check=full ./castle castle1p.dat -d

run_deterministic_with_log1:
	@echo ">>>>>> Running castle with deterministic seed, LOG and valgrind"
	valgrind --leak-check=full ./castle castle1p.dat -d -l output.log

run_cmd1: dirs
	@echo ">>>>>> Running castle with cmd, LOG and valgrind"
	valgrind --leak-check=full ./castle castle1p.dat -d -l $(LOGDIR)/proof1p.log < $(CMDDIR)/proof1p.cmd
	diff -i $(LOGDIR)/proof1p.log $(TXTDIR)/proof1p.txt

run_cmd_win1: dirs
	@echo ">>>>>> Running castle with cmd, LOG and valgrind"
	valgrind --leak-check=full ./castle castle1p.dat -d -l $(LOGDIR)/win1.log < $(CMDDIR)/win1.cmd
	diff -i -w $(LOGDIR)/win1.log $(TXTDIR)/win1.txt

#############################################################################
# RUN 2 PLAYERS


runv2:
	@echo ">>>>>> Running castle with valgrind"
	valgrind --leak-check=full ./castle castle2p.dat

run_log2:
	@echo ">>>>>> Running castle with LOG and valgrind"
	valgrind --leak-check=full ./castle castle2p.dat -l output.log

run_deterministic2:
	@echo ">>>>>> Running castle with deterministic seed and valgrind"
	valgrind --leak-check=full ./ castle.dat -d

run_deterministic_with_log2:
	@echo ">>>>>> Running castle with deterministic seed, LOG and valgrind"
	valgrind --leak-check=full ./castle castle2p.dat -d -l output.log

run_cmd_win2: dirs
	@echo ">>>>>> Running castle with cmd, LOG and valgrind"
	valgrind --leak-check=full ./castle castle2p.dat -d -l $(LOGDIR)/win2.log < $(CMDDIR)/win2.cmd
	diff -i -w $(LOGDIR)/win2.log $(TXTDIR)/win2.txt



#############################################################################
#PRESENTACION

run:
	@echo ">>>>>> Running castle"
	./castle castle3.dat -d

run_win1: dirs
	@echo ">>>>>> Running castle"
	./castle castle1p.dat -d -c $(CMDDIR)/win1.cmd

run2:
	@echo ">>>>>> Running castle"
	./castle castle2p.dat -d
#############################################################################

run_tests: 
	./tests.sh 1

#############################################################################

.PHONY: all clear clean run runv run_log run_cmd tests run_tests run_continue1

#############################################################################

doxygen:
	@echo ">>>>>> Executing Doxygen"
	doxygen Doxyfile