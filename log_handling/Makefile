CFLAGS := -Wall -Wextra -Werror
PROG := build/state_sort.out
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
--linelength=110 ./src
CPPCHECHCFG = --enable=all --suppress=missingIncludeSystem

all: clean state_sort.c

build:
#	@mkdir build 2>/dev/null
	@gcc $(CFLAGS) src/state_sort.c -o $(PROG)

state_sort.c:
	@gcc $(CFLAGS) src/state_sort.c -o $(PROG)

# Проверки и очистка

check:
	@echo " "
# Рекурсивно проверяет все файлы с перечисленными расширениями, начиная от текущей (.) директории
	@python3 materials/linters/cpplint.py $(LINTERCFG)
	@echo " "
# Рекурсивно проверяет все файлы, начиная от текущей (.) директории
	@cppcheck $(CPPCHECKCFG) .

leaks:
# For MacOS. "| grep LEAK:" используется для короткого вывода, чтобы видеть только линии с утечками, если они есть.
#	@leaks -atExit -- ./$(PROG)

# For Linux. "-q" - quiet, run silently; only print error msgs
	@valgrind  -q --leak-check=full $(PROG)

clean:
	@rm -rf src/*.o
	@rm -rf src/*.a
	@rm -rf src/*.so
	@rm -rf src/*.out
	@rm -rf build/*.out

rebuild:
	@make clean
	@make