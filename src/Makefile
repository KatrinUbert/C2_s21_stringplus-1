CC = gcc
C_FLAGS = -Wall -Werror -Wextra -std=c11 -g

OS = $(shell uname -s)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -pthread -lcheck_pic -lrt -lm -lsubunit
else
	CHECK_FLAGS = -lcheck
endif

all: s21_strings

s21_strings: clean_all test clean

test: s21_string.a ./test.c
	${CC} ${C_FLAGS} -c -o ./test.o ./test.c
	${CC} ${C_FLAGS} ./test.o -o ./test -L ./ s21_string.a ${CHECK_FLAGS}

s21_string.a: s21_string.o s21_string_part5.o s21_sprintf.o
	ar q s21_string.a ./s21_string.o ./s21_string_part5.o ./s21_sprintf.o

s21_sprintf.o: ./s21_sprintf.c
	${CC} ${C_FLAGS} -c -o ./s21_sprintf.o ./s21_sprintf.c

s21_string_part5.o: s21_string.o ./s21_string_part5.c
	${CC} ${C_FLAGS} -c -o ./s21_string_part5.o ./s21_string_part5.c

s21_string.o: ./s21_string.c
	${CC} ${C_FLAGS} -c -o ./s21_string.o ./s21_string.c

SRC_C_FILES := $(shell find $(SRC_DIR) -name "s21_*.c")

gcov_report: clean_all s21_string.a
	${CC} ${C_FLAGS} --coverage test.c $(SRC_C_FILES) s21_string.a -L. s21_string.a ${CHECK_FLAGS} -o ./test_gcov
	./test_gcov
	lcov -t "Report" -c -d ./ --output-file ./coverage.info
	genhtml ./coverage.info --output-directory ./report/
	make clean
	open $(BUILD_PATH)report/index.html

clean_all:
	make clean
	rm -rf ./*.a ./test ./tests ./coverage.info ./report

clean:
	rm -rf ./*.o
	rm -rf ./test_gcov*