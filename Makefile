.PHONY: run

database: database.c
	gcc database.c -o database

run: database
	./database
