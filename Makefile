# DXGI_FLAGS = -ldxgi -ldxguid -lole32 //needed to link while using wincore library

SourceFiles = ./obj/cpu.o ./obj/gpu.o ./obj/memory.o ./obj/OS.o ./obj/locale.o ./obj/hostname.o ./obj/uptime.o ./obj/display.o ./obj/username.o

OBJ_FOLDER = obj

all: $(SourceFiles)

#create folder to store .o files
$(OBJ_FOLDER):
	mkdir $(OBJ_FOLDER)

#check if obj folder exsists if not create then output .o files there
#% placeholder for file names
$(OBJ_FOLDER)/%.o: ./src/%.c | $(OBJ_FOLDER)
	gcc -c -I"./headers" $< -o $@

clean-obj:
	powershell -Command "Remove-Item -Recurse -Force ./obj/*"
