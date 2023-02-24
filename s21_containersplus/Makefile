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

all: test

test: test_multi

test_multi:
	$(CC) $(FLAGS) -I. -I../s21_binary_tree ../tests/test_multiset.cc $(INCLUDE) \
											../s21_binary_tree/s21_tree.h $(TEST_FLAGS) -o s21_test_multi
	./s21_test_multi

gcov_report:FLAGS += $(GCOV)
gcov_report: clean test
	lcov -t "gcov_report" --no-external -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info;
	open ./report/index.html

valgrind:
ifeq ($(UNAME), Linux)
	valgrind --leak-check=full ./s21_test_multi
else
	leaks --atExit -- ./s21_test_multi
endif

check:
	bash ../tests/style.sh
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.h ../tests/test_multiset.cc

clean:
	rm -rf objects *.gcno *.gcda *.o *.info report s21_test_multi \
	../s21_binary_tree/*.gch ../s21_binary_tree/s21_test_tree