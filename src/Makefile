CFLAGS = -std=c11 -Wall -Wextra -Werror	
TESTS = tests/test_tetris.c
FLAG_TEST = -lcheck -lsubunit -lm
LIBS = -lncurses 
TARGETS = brick_game/*.c gui/cli.c


all: clean install gcov_report

dvi:
	open instruction.md

dist: clean install
	mkdir build && mv tetris build
	cp instruction.md build
	tar cvzf Tetris.tgz build/

test: clean
	gcc $(CFLAGS) $(TARGETS) $(TESTS) $(LIBS) $(FLAG_TEST) -o tetris && ./tetris

gcov_report:
	gcc --coverage $(TARGETS) $(TESTS) $(LIBS) $(FLAG_TEST) -o greport
	./greport
	lcov -t "s21_tetris" -o s21_tetris.info -c -d .
	genhtml -o ./report s21_tetris.info
	open ./report/index.html


install: clean
	gcc $(CFLAGS) $(TARGETS) main.c -lncurses -o tetris

uninstall: clean

check_style: clean
	clang-format -n brick_game/*.h brick_game/*.c tests/*.c   main.c gui/*.h gui/*.c -style='{BasedOnStyle: Google, ColumnLimit: 150, IndentWidth: 4}'

style: clean
	clang-format -i brick_game/*.h brick_game/*.c tests/*.c   main.c gui/*.h gui/*.c -style='{BasedOnStyle: Google, ColumnLimit: 150, IndentWidth: 4}'

clean:
	rm -rf brick_game/*.o gui/*.o *.o *.gcno *.gcda *.info gcov_report report greport tetris build Tetris.tgz