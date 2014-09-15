CC = gcc
CFLAGS = -std=c99

.PHONY: run test

main: src/main.c include/util.h include/database.h src/database.c
	mkdir -p dist; $(CC) $(CFLAGS) -Iinclude -Ivendor/hash src/main.c src/database.c vendor/hash/hash.c -o dist/main

run: main
	dist/main

test-dist/%_test: src/%.c test/%_test.c
	mkdir -p test-dist; $(CC) $(CFLAGS) -Iinclude -Ivendor/hash -Ivendor/seatest $^ vendor/hash/hash.c vendor/seatest/seatest.c -o $@

test: test-dist/$(test)_test
	test-dist/$(test)_test
