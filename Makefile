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
TESTS_LDFLAGS = -lcriterion --coverage
TESTS_COVERAGE_DIR = $(TESTS_DIR)/coverage

all: $(NAME)

$(NAME): $(OBJ) $(MAIN_OBJ)
	$(CC) $(OBJ) $(MAIN_OBJ) -o $(NAME) $(LDLIBS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

debug:
	$(CC) $(DEBUG_FLAGS) $(SRC) $(MAIN) -o $(NAME) $(CFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJ)
	rm -Rf $(TESTS_COVERAGE_DIR) $(TESTS)
	rm -f *.gcno *.gcda *.gcov *.html *.css *.js

fclean: clean
	rm -f $(NAME)history

re: fclean all

$(TESTS): $(TESTS_SRC) $(SRC)
	$(CC) $(TESTS_SRC) $(SRC) -o $(TESTS) $(CFLAGS) $(TESTS_LDFLAGS) $(LDLIBS)
	mkdir -p $(TESTS_COVERAGE_DIR)
	mv *.gcno $(TESTS_COVERAGE_DIR) || true

tests_run: $(TESTS)
	./$(TESTS)
	mkdir -p $(TESTS_COVERAGE_DIR)
	rm -f $(TESTS_COVERAGE_DIR)/*.gcda || true
	mv *.gcda $(TESTS_COVERAGE_DIR) || true

tests_show: tests_run
	mv $(TESTS_COVERAGE_DIR)/*.gcda . || true
	mv $(TESTS_COVERAGE_DIR)/*.gcno . || true
	gcovr --gcov-executable "llvm-cov gcov" --html-details coverage.html
	mv *.gcno $(TESTS_COVERAGE_DIR) || true
	mv *.gcda $(TESTS_COVERAGE_DIR) || true
	mv *.gcov $(TESTS_COVERAGE_DIR) || true
	mv *.html $(TESTS_COVERAGE_DIR) || true
	mv *.css $(TESTS_COVERAGE_DIR) || true
	mv *.js $(TESTS_COVERAGE_DIR) || true
	firefox $(TESTS_COVERAGE_DIR)/coverage.html

sanity_check:
	scan-build --status-bugs -disable-checker unix.Malloc make re;

.PHONY: all clean fclean re debug tests_run tests_clean tests_re
