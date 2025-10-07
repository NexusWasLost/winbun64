CC = gcc

DXGI_FLAGS = -ldxgi -ldxguid -lole32

SourceFiles = ./src/main.c ./src/memory.c ./src/gpu.c ./src/cpu.c ./src/OS.c ./src/locale.c ./src/hostname.c ./src/uptime.c ./src/display.c ./src/username.c

all: winfetch.exe

winfetch.exe:
	$(CC) $(SourceFiles) $(DXGI_FLAGS) -o winfetch
