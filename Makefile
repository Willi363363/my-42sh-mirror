##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Compile minishell
##

SRC = 	$(shell find ./src -name "*.c")

CC = epiclang

CFLAGS = -Iincludes -Wall -Wextra -W

LDLIBS = -lncurses

DEBUG_FLAGS = -g3

OBJ = $(SRC:.c=.o)
NAME = 42sh

# --- Unit Tests ---
TESTS = unit_tests
TESTS_SRC = $(shell find tests -name '*.c')
TESTS_OBJ = $(TESTS_SRC:.c=.o)
TESTS_LDFLAGS = -lcriterion --coverage

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDLIBS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

debug :
	$(CC) $(DEBUG_FLAGS) $(SRC) -o $(NAME) $(CFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJ) $(TESTS_OBJ)
	rm -f *.gcda *.gcno *.pch

fclean: clean
	rm -f $(NAME) history

re: fclean all

unit_tests: $(TESTS_OBJ)
	$(CC) $(TESTS_OBJ) -o $(TESTS) $(TESTS_LDFLAGS)

sanity_check:
	scan-build --status-bugs -disable-checker unix.Malloc make re;

.PHONY: all clean fclean re debug tests_run tests_clean tests_re