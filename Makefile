DXGI_FLAGS = -ldxgi -ldxguid -lole32

SourceFiles = main.o gpu.o cpu.o memory.o OS.o locale.o hostname.o uptime.o display.o username.o

all: winfetch.exe

%.o: ./src/%.c
	gcc -c $< -o $@

winfetch.exe: $(SourceFiles)
	gcc $(SourceFiles) $(DXGI_FLAGS) -o winfetch.exe
