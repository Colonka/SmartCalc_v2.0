CFLAGS = -Wall -Werror -Wextra -std=c17
CC = g++

ARCHIVE = s21_calc_v2.0

all: install

test: clean
	mkdir build
	cmake -S ./ -B build -DCALC_TESTING=ON
	cmake --build build --target check

install: clean
	mkdir -p build
	cmake -S ./ -B build
	cmake --build build

run:
	open -Fn build/s21_calc.app

uninstall: 
	rm -rf build
	rm -rf test_build
	rm -rf docs

dvi: clean
	mkdir -p docs
	doxygen Doxyfile
	mv html latex docs
	open docs/html/index.html

dvi_open:
	open docs/html/index.html

dist: clean install
	tar -cf $(ARCHIVE).tar build/*

gcovr_report: clean
	mkdir build
	mkdir report
	cmake -S ./ -B build -DCALC_TESTING=ON -DCALC_COVERAGE=ON
	cmake --build build --target coverage
	open report/report.html
	
git: clean
	git add -A
	git commit -m "$m"
	git push origin "$b"

test_no_run: clean
	mkdir build
	cmake -S ./ -B build -DCALC_TESTING=ON
	cmake --build build

check: clean test_no_run
	cd build/test && leaks --atExit -- ./s21_calc_test

clean:
	rm -rf s21_calc/*.user build test_build CMakeLists.txt.user report docs .clang-format

		 