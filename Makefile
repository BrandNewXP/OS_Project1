all: main.c process.c scheduler.c headers.h
	gcc main.c process.c scheduler.c -o main