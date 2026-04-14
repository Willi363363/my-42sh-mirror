##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Compile minishell
##

SRC = 	./src/main.c \
		./src/env_parse.c \
		./src/shell_commands/misc/misc_builtins.c \
		./src/cleanup_functions/free_struct.c \
		./src/tokenizers.c \
		./src/lib/str_to_word_array.c \
		./src/lib/my_replace_char.c \
		./src/lib/my_str_remove_char.c \
		./src/lib/my_str_count_char.c \
		./src/lib/my_safe_free.c \
		./src/lib/my_strdup.c \
		./src/lib/my_strdup_skip_chars.c \
		./src/lib/my_strlen.c \
		./src/lib/my_tablen.c \
		./src/lib/my_strcmp.c \
		./src/lib/my_strcpy.c \
		./src/lib/my_strcpy_limit.c \
		./src/lib/my_strcat.c \
		./src/lib/my_putstr.c \
		./src/lib/my_putstr_error.c \
		./src/lib/my_put_nbr.c \
		./src/lib/my_putchar.c \
		./src/lib/my_strncmp.c \
		./src/lib/my_check_if_alphanums.c \
		./src/shell_commands/system_cmds.c \
		./src/shell_commands/own_files_cmds.c \
		./src/shell_commands/directories_related/dir_cmds.c \
		./src/shell_commands/directories_related/dir_functions.c \
		./src/shell_commands/env_related/env_cmds.c \
		./src/shell_commands/env_related/setenv.c \
		./src/shell_commands/env_related/unsetenv.c \
		./src/parsing/parsing.c \
		./src/parsing/lexer.c \
		./src/parsing/tokenize/tokenize.c \
		./src/parsing/tokenize/operators.c \
		./src/parsing/launcher/launcher.c \
		./src/parsing/launcher/executing/exec.c \
		./src/parsing/launcher/executing/exec_bis.c \
		./src/parsing/launcher/executing/error_handling.c

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
	$(CC) $(CFLAGS) -c $< -o $@

debug:
	$(CC) $(DEBUG_FLAGS) $(SRC) -o $(NAME)

# Compilation des tests
$(TESTS): $(TESTS_OBJ) $(OBJ)
	$(CC) $(CFLAGS) $(TESTS_LDFLAGS) $^ -o $@

tests_run: $(TESTS)
	@echo "Running unit tests..."
	@./$(TESTS)

tests_clean:
	rm -f $(TESTS_OBJ) $(TESTS)

tests_re: tests_clean tests_run

clean:
	rm -f $(OBJ) $(TESTS_OBJ)
	rm -f *.gcda *.gcno *.pch

fclean: clean
	rm -f $(NAME) $(TESTS) secured

re: fclean all

.PHONY: all clean fclean re debug tests_run tests_clean tests_re