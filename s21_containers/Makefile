CC=g++
FLAGS=-Wall -Wextra -Werror -g --std=c++17
GCOV=-coverage
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	TEST_FLAGS=-lgtest -lpthread
endif

TEST_DIR=../tests/

.PHONY: all clean test gcov_report

all: test

test: test_list test_set test_vector

test_list:
	$(CC) $(FLAGS) -I. s21_list.h $(TEST_DIR)test_list.cc $(TEST_FLAGS) -o s21_test_list
	./s21_test_list

test_set:
	$(CC) $(FLAGS) -I. -I../s21_binary_tree s21_set.h ../s21_binary_tree/s21_tree.h $(TEST_DIR)test_set.cc $(TEST_FLAGS) -o s21_test_set
	./s21_test_set

test_vector:
	$(CC) $(FLAGS) -I. s21_vector.h $(TEST_DIR)test_vector.cc $(TEST_FLAGS) -o s21_test_vector
	./s21_test_vector

gcov_report:FLAGS += $(GCOV)
gcov_report: clean test
	lcov -t "gcov_report" --no-external -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info;
	open ./report/index.html

check:
	bash ../style.sh
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.h \
																		../tests/test_list.cc \
																		../tests/test_set.cc \
																		../tests/test_vector.cc

valgrind: test_list test_set test_vector
ifeq ($(UNAME), Linux)
	valgrind --leak-check=full ./s21_test_list ./s21_test_set ./s21_test_vector
else
	leaks --atExit -- test_list ./s21_test_set ./s21_test_vector
endif


clean:
	rm -rf objects *.gcno *.gcda *.o *.info report s21_test_vector s21_test_set s21_test_list \
	../s21_binary_tree/*.gch ../s21_binary_tree/s21_test_tree