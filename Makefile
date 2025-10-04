CC = gcc

DXGI_FLAGS = -ldxgi -ldxguid -lole32

SourceFiles = ./src/main.c ./src/memory.c ./src/gpu.c ./src/cpu.c

all: winfetch.exe

winfetch.exe:
	$(CC) $(SourceFiles) $(DXGI_FLAGS) -o winfetch
