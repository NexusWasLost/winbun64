DXGI_FLAGS = -ldxgi -ldxguid -lole32

SourceFiles = ./obj/main.o ./obj/gpu.o ./obj/cpu.o ./obj/memory.o ./obj/OS.o ./obj/locale.o ./obj/hostname.o ./obj/uptime.o ./obj/display.o ./obj/username.o

OBJ_FOLDER = obj

all: winfetch.exe

#create folder to store .o files
$(OBJ_FOLDER):
	mkdir $(OBJ_FOLDER)

#check if obj folder exsists if not create then output .o files there
#% placeholder for file names
$(OBJ_FOLDER)/%.o: ./src/%.c | $(OBJ_FOLDER)
	gcc -c $< -o $@

winfetch.exe: $(SourceFiles)
	gcc $(SourceFiles) $(DXGI_FLAGS) -o winfetch.exe

clean-obj:
	powershell -Command "Remove-Item -Recurse -Force ./obj/*"

remove-exe:
	powershell -Command "Remove-Item -Force ./winfetch.exe"
