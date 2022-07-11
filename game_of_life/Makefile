CFLAGS := -Wall -Wextra -Werror
PROG := game_of_life.out
LINTERCFG = --extensions=c,h $\
--filter=-runtime/int,$\
-legal/copyright,$\
-build/include_subdir,$\
-build/include,$\
-readability/casting,$\
-runtime/threadsafe_fn,$\
-runtime/printf $\
--headers=h $\
--recursive $\
--linelength=110
CPPCHECHCFG = --enable=all --suppress=missingIncludeSystem

.PHONY: all clean

all: clean build

build:
	gcc $(CFLAGS) game_of_life.c -o $(PROG) -lncurses -lrt

game_of_life.c:
	gcc $(CFLAGS) game_of_life.c -o $(PROG) -lncurses -lrt

# Проверки и очистка

check:
	@echo " "
# Рекурсивно проверяет все файлы с перечисленными расширениями, начиная от текущей (.) директории
	python3 cpplint.py $(LINTERCFG) .
	@echo " "
# Рекурсивно проверяет все файлы, начиная от текущей (.) директории
	cppcheck $(CPPCHECKCFG) .

leaks:
# For MacOS. "| grep LEAK:" используется для короткого вывода, чтобы видеть только линии с утечками, если они есть.
#	@leaks -atExit -- ./$(PROG)

# For Linux. "-q" - quiet, run silently; only print error msgs
	valgrind  -q --leak-check=full ./$(PROG)

clean:
	@rm -rf *.o
	@rm -rf *.a
	@rm -rf *.so
	@rm -rf *.out

rebuild:
	@make clean
	@make