.PHONY: run

main: main.c util.h database.h database.c
	gcc main.c database.c -o main

run: main
	./main
