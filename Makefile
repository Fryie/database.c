.PHONY: run

main: src/main.c include/util.h include/database.h src/database.c
	mkdir -p dist; gcc -Iinclude src/main.c src/database.c -o dist/main

run: main
	dist/main
