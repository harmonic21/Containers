CC=g++
FLAGS=-Wall -Wextra -Werror -g --std=c++17
GCOV=-coverage
UNAME:= $(shell uname)

ifeq ($(UNAME), Linux)
	TEST_FLAGS=-lgtest -lpthread
endif

.PHONY: all clean test gcov_report

all: test

test:
	$(CC) $(FLAGS) -I. s21_tree.h ../tests/test_tree.cc $(TEST_FLAGS) -o s21_test_tree
	./s21_test_tree

gcov_report:FLAGS += $(GCOV)
gcov_report: clean test
	lcov -t "gcov_report" --no-external -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info;
	open ./report/index.html

valgrind: test
ifeq ($(UNAME), Linux)
	valgrind --leak-check=full ./s21_test_tree
else
	leaks --atExit -- ./s21_test_tree
endif

check:
	bash ../style.sh
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.h ../tests/test_tree.cc

clean:
	rm -rf objects *.gcno *.gcda *.o *.info report s21_test_tree