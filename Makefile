CC = gcc

SourceFiles = ./src/duckz.c ./src/memory.c

all: duckz.exe

duckz.exe:
	$(CC) $(SourceFiles) -o duckz
