##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Compile minishell
##

SRC = 	$(shell find ./src -name "*.c")

CC = epiclang
CFLAGS = -Wall -Wextra -Iincludes
DEBUG_FLAGS = -g3 $(CFLAGS)

OBJ = $(SRC:.c=.o)
NAME = 42sh

# --- Unit Tests ---
TESTS = unit_tests
TESTS_SRC = $(shell find tests -name '*.c')
TESTS_OBJ = $(TESTS_SRC:.c=.o)
TESTS_LDFLAGS = -lcriterion --coverage

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) -c $< -o $@ -Iincludes -lncurses

debug :
	$(CC) $(DEBUG_FLAGS) $(SRC) -o $(NAME) -Iincludes -lncurses

clean:
	rm -f $(OBJ) $(TESTS_OBJ)
	rm -f *.gcda *.gcno *.pch

fclean: clean
	rm -f $(NAME) $(TESTS) secured

re: fclean all

.PHONY: all clean fclean re debug tests_run tests_clean tests_re