CC=g++
FLAGS=-Wall -Wextra -Werror -g --std=c++11
GCOV=-coverage
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	TEST_FLAGS=-lgtest -lpthread
endif


#INCLUDES
INCLUDE=s21_multiset.h

.PHONY: all clean test gcov_report

all: build

build:
	$(CC) $(FLAGS) -I../s21_binary_tree s21_containersplus.h -o s21_containersplus

test: test_multi

test_multi:
	$(CC) $(FLAGS) -I. -I../s21_binary_tree ../tests/test_multiset.cc $(INCLUDE) ../s21_binary_tree/s21_tree.h $(TEST_FLAGS) -o s21_test
	./s21_test

gcov_report:FLAGS += $(GCOV)
gcov_report: clean test
	./s21_test
	lcov -t "gcov_report" --no-external -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info;
	open ./report/index.html

valgrind:
ifeq ($(UNAME), Linux)
	valgrind --leak-check=full ./s21_test
else
	leaks --atExit -- ./s21_test
endif


clean:
	rm -rf objects *.gcno *.gcda *.o *.info report s21_test \
	../s21_binary_tree/*.gch ../s21_binary_tree/s21_test