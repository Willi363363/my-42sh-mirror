##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Compile minishell
##

SRC = 	$(shell find ./src -name "*.c")

CC = epiclang

CFLAGS = -Iincludes

LDLIBS = -lncurses

DEBUG_FLAGS = -g3 -Wall -Wextra

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
	rm -f $(NAME) $(TESTS) secured

re: fclean all

.PHONY: all clean fclean re debug tests_run tests_clean tests_re