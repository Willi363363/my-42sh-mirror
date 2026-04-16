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

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDLIBS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

debug :
	$(CC) $(DEBUG_FLAGS) $(SRC) -o $(NAME) $(CFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJ)
	rm -f *.gcda *.gcno *.pch

fclean: clean
	rm -f $(NAME) secured

re: fclean all
