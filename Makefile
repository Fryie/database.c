.PHONY: run test

main: src/main.c include/util.h include/database.h src/database.c
	mkdir -p dist; gcc -Iinclude src/main.c src/database.c -o dist/main

run: main
	dist/main

test-dist/%_test: src/%.c test/%_test.c
	mkdir -p test-dist; gcc -Iinclude -Ivendor/seatest $^ vendor/seatest/seatest.c -o $@

test: test-dist/$(test)_test
	test-dist/$(test)_test
