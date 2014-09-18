CC = gcc
CFLAGS = -std=c99
DEBUG_CFLAGS = -std=c99 -g -O0
VALGRIND_OPTS = --leak-check=full --show-leak-kinds=all

.PHONY: run test valgrind

dist/main: src/main.c include/util.h include/database.h src/database.c
	mkdir -p dist; $(CC) $(CFLAGS) -Iinclude -Ivendor/hash -Ivendor/vec src/main.c src/database.c vendor/hash/hash.c vendor/vec/vec.c -o dist/main

dist/main_debug: src/main.c include/util.h include/database.h src/database.c
	mkdir -p dist; $(CC) $(DEBUG_CFLAGS) -Iinclude -Ivendor/hash -Ivendor/vec src/main.c src/database.c vendor/hash/hash.c vendor/vec/vec.c -o dist/main_debug

run: dist/main
	dist/main

test-dist/%_test: src/%.c test/%_test.c
	mkdir -p test-dist; $(CC) $(DEBUG_CFLAGS) -Iinclude -Ivendor/hash -Ivendor/vec -Ivendor/seatest $^ vendor/hash/hash.c vendor/vec/vec.c vendor/seatest/seatest.c -o $@

test: test-dist/$(test)_test
	test-dist/$(test)_test

valgrind: dist/main_debug
	valgrind $(VALGRIND_OPTS) dist/main_debug

test_valgrind: test-dist/$(test)_test
	valgrind $(VALGRIND_OPTS) test-dist/$(test)_test
