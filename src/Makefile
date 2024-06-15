CC = gcc
FLAGS = -std=c11 -g -Wall -Werror -Wextra
GLFLAGS = --coverage
FILENAME = s21_matrix
LIBNAME = $(FILENAME).a

SOURCE_TEST_C = $(wildcard ./tests/s21_*.c)
SOURCE_TEST_H = $(wildcard ./tests/s21_*.h)

S21_C = s21_*.c
S21_H = s21_*.h
S21_O = s21_*.o
TESTS = test
SYSTEM := $(shell uname -s)

ifeq ($(SYSTEM), Linux)
    	# Код для компиляции под Linux
		OPEN_CMD = xdg-open
			ADD_LIB =  -lcheck -lm -lsubunit
else ifeq ($(SYSTEM), Darwin)
			# Код для компиляции под macOS
		OPEN_CMD = open
			ADD_LIB = -lcheck
		BREW := ${HOME}/homebrew
else
    $(error Unsupported system: $(SYSTEM))
endif

PATH := $(BREW)/bin:$(PATH)

all: $(LIBNAME) gcov_report

$(LIBNAME): 
		$(CC) $(FLAGS) -c $(S21_C)
		ar rcs $(LIBNAME) $(S21_O)
		ranlib $(LIBNAME)

s21_covered:
		$(CC) $(FLAGS) -c $(S21_C) ${SOURCE_TEST_C} $(GLFLAGS)
		ar rc $(LIBNAME) $(S21_O)
		ranlib $(LIBNAME)

test: clean $(LIBNAME)
		$(CC) ${SOURCE_TEST_C} -c $(FLAGS) $(GLFLAGS)
		$(CC) s21_*.o $(LIBNAME) -o $(TESTS) ${ADD_LIB} $(FLAGS) $(GLFLAGS)
		./$(TESTS)

tests: clean $(LIBNAME)
		# $(CC) $(FLAGS) -c $(S21_C) ./tests/test.c
		$(CC) test.o $(LIBNAME) -o test ${ADD_LIB} $(FLAGS)
		./test

testc: clean s21_covered
		$(CC) ${SOURCE_TEST_C} -c $(FLAGS) $(GLFLAGS)
		$(CC) s21_*.o $(LIBNAME) -o $(TESTS) ${ADD_LIB} $(FLAGS) $(GLFLAGS)
		./$(TESTS)

install:
		if [ $(SYSTEM) = "Linux" ]; then \
			sudo apt-get install -y lcov; \
			sudo apt-get install -y check; \
			sudo apt-get install -y libcapture-tiny-perl; \
			sudo apt-get install -y libdatetime-perl; \
		else \
			brew install lcov; \
		fi

gcov_report: testc
		./$(TESTS)
		lcov -t "$(FILENAME)" -o $(FILENAME).info -c -d . --no-external 
		genhtml -o report $(FILENAME).info  
		open report/index.html

test_sega: clean $(LIBNAME) 
		$(CC) $(FLAGS)  $(SOURCE_TEST_C) -L. $(LIBNAME) -o $(TESTS) $(ADD_LIB) -fsanitize=address -g
		./$(TESTS)

leaks: clean test
		valgrind --tool=memcheck --leak-check=full --show-reachable=yes --track-origins=yes ./$(TESTS)

check:
		clang-format -style=google -i *.c *.h ${SOURCE_TEST_C} ${SOURCE_TEST_H}
		cppcheck enable=all missningIncludeSystem ${SOURCE_TEST_C}
		cppcheck enable=all missningIncludeSystem ./$(S21_C)

pcheck:
		clang-format -style=google -n *.c *.h ${SOURCE_TEST_C} ${SOURCE_TEST_H}
		cppcheck enable=all missningIncludeSystem ${SOURCE_TEST_C}
		cppcheck enable=all missningIncludeSystem ./$(S21_C)
		
clean:
		rm -rf *.gcno *.html report
		rm -rf *.gcov 
		rm -rf *.gcda
		rm -rf $(TESTS) *.a
		rm -rf *.info
		rm -rf *.o
		rm -rf *.out
		rm -rf *.dSYM

aclean:
		rm -rf *.gcno *.html report
		rm -rf *.gcov 
		rm -rf *.gcda
		rm -rf $(TESTS)
		rm -rf *.info
		rm -rf *.o
		rm -rf *.out
		rm -rf test.dSYM

rebuild: clean all