##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Compile minishell
##
CC = epiclang
CFLAGS = -Iinclude -Wall -Wextra -W
LDLIBS = -lncurses
DEBUG_FLAGS = -g3

SRC_DIR = src
SRC = $(shell find $(SRC_DIR) -name "*.c")
OBJ = $(SRC:.c=.o)
NAME = 42sh
MAIN = main.c
MAIN_OBJ = $(MAIN:.c=.o)

# --- Unit Tests ---
TESTS = unit_tests
TESTS_DIR = tests
TESTS_SRC = $(shell find $(TESTS_DIR) -name '*.c')
TESTS_OBJ = $(TESTS_SRC:.c=.o)
TESTS_LDFLAGS = -lcriterion --coverage

all: $(NAME)

$(NAME): $(OBJ) $(MAIN_OBJ)
	$(CC) $(OBJ) $(MAIN_OBJ) -o $(NAME) $(LDLIBS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

debug:
	$(CC) $(DEBUG_FLAGS) $(SRC) $(MAIN) -o $(NAME) $(CFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJ) $(TESTS_OBJ)
	rm -f *.gcda *.gcno *.pch

fclean: clean
	rm -f $(NAME) history

re: fclean all

$(TESTS): $(TESTS_OBJ) $(OBJ)
	$(CC) $(TESTS_OBJ) $(OBJ) -o $(TESTS) $(TESTS_LDFLAGS) $(LDLIBS)

tests_run: $(TESTS)
	./$(TESTS)

sanity_check:
	scan-build --status-bugs -disable-checker unix.Malloc make re;

.PHONY: all clean fclean re debug tests_run tests_clean tests_re
