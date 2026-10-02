# WinBun64

WinBun64 is a lightweight C library for fetching system information on Windows.

WinBun64 is written in C but is compatible with both C and C++.

## Supported Constraints

- *CPU Architectures:* x86_64 (64 bit, AMD64), should work on x86 (32  bit systems; Not tested).

- *Maximum Monitor Resolutions:* 4.

- *Maximum GPUs:* 4.

- *Windows Version Tested:* Windows 11 and Windows 10 (may work on 7, 8, 8.1, Vista, XP; Not tested).

- *Compilers:* WinBun64 is compiled using [GCC (MinGW)](https://nuwen.net/mingw.html) so its fully supported; [Clang](https://clang.llvm.org/) should work (not tested); [MSVC](https://visualstudio.microsoft.com/vs/features/cplusplus/) **not supported** without changing source code and rebuild.

## Downloading the Library

WinBun64 is shipped as a static library (`.a`) alongside headers files in an "include" folder.

- `include/` - contains `winbun.h` and `winbun_functions.h`.
- `lib/` - contains `libwinbun.a` (the actual library).

To get started, download the library from [releases](https://github.com/NexusWasLost/winbun64/releases/).

### 🔰 Example Code

```c
#include <stdio.h>
#include "winbun.h"
#include "winbun_functions.h"

int main(){
	WINBUN bun; //define a WINBUN variable

	getCPU(&bun); //call needed function
	getMemory(&bun);
	getDisplay(&bun);

	//print the info
	printf("CPU: %s\n", bun.CPU);
	printf("RAM: %llu MB / %llu MB\n", bun.usedMemory, bun.totalMemory);

	//print all active displays.
	printf("Resolution: ");
	for(int x = 0; x < bun.displayCount; x++){
        printf("%dx%d @ %dHz\n", bun.monitors[x].width, bun.monitors[x].height, bun.monitors[x].refreshRate);
    }

	return 0;
}
```

Each function populates a struct variable named `bun` with respective info.

Assuming the code file is called `main.c`, Compile using `gcc`:

```shell
gcc main.c -o main.exe -I"path-to-include-headers" -L"path-to-library" -lwinbun -ldxgi -ldxguid -lole32
```

**IMPORTANT:** WinBun64 depends on Windows provided Libraries such as `dxgi`, `dxguid` and `ole32` as it uses `DXGI` for GPU information therefore these needs to be linked while producing an `exe`.

## Building from Source

The library can be built from source if needed.

*Compiler:* GCC or Clang, make or mingw32-make for makefiles and CMake.

1. Clone the repository

```shell
git clone https://github.com/NexusWasLost/winbun64.git
```

2. Navigate into the directory

```shell
cd winbun64
```

### Using CMake (Recommended)

1. Initialize CMake
```shell
cmake -B build -G "MinGW Makefiles"
```

2. Build the library (CMake creates it in build directory)
```shell
cmake --build build
```

### Using Makefile

1. Build  using Make
```shell
make
```

---

### 🔸 **Building with MSVC**

(Not Tested) In `cpu.c`, replace GCC specific - `<cpuid.h>` and `__get_cpuid()` with MSVC equivalents:

```c
...
#include <intrin.h> //include intrin.h instead of cpuid.h
...
void getCPU(WINBUN* bun){
	...
	int cpuBrandString[4];
	for(int x = 0; x < 3; x++){
		__cpuid(cpuBrandString, 0x80000002 + x) //call __cpuid()
		...
	}
}
```

Now build using CMake (CMake targets MSVC NMake by default on Windows)

```shell
cmake -B build
```
```shell
cmake --build build
```

---

## 💎 List of Fields and Functions

| Field                                   | Type                              | Populated by Function     | Description                              |
| --------------------------------------- | --------------------------------- | ------------------------- | ---------------------------------------- |
| `CPU`                                   | `char[]`                          | `getCPU()`                | CPU Brand String                         |
| `CPU_Architecture`                      | `char[]`                          | `getCPU()`                | CPU Architecture                         |
| `OS_ProductName`                        | `char[]`                          | `getOS()`                 | Windows Product Name                     |
| `OS_version`                            | `char[]`                          | `getOS()`                 | OS version String                        |
| `OS_buildNumber`                        | `char[]`                          | `getOS()`                 | Windows Build Number                     |
| `host`                                  | `char[]`                          | `getHostName()`           | Computer Hostname                        |
| `locale`                                | `wchar_t[]`                       | `getLocale()`             | System Locale                            |
| `currentUserName`                       | `char[]`                          | `getCurrentUsername()`    | Logged in username                       |
| `totalMemory`                           | `unsigned long long`              | `getMemory()`             | Total Physical Memory (in MB)            |
| `availableMemory`                       | `unsigned long long`              | `getmemory()`             | Total Available Memory (in MB)           |
| `usedMemory`                            | `unsigned long long`              | `getMemory()`             | Total Used Memory (in MB)                |
| `memoryLoad`                            | `unsigned long long`               | `getMemory()`             | Current Memory Load (Percentage)         |
| `uptime`                                | `unsigned long long`              | `getUptime()`             | System Uptime (in seconds)               |
| `gpu`                                   | `GPU` struct Array                | `getGPU()`                | List of GPUs Detected                    |
| `GPU (GPU_Name, totalVRAM)`             | `wchar_t[]`, `unsigned long long` | *within `GPU` struct*     | GPU Name and total VRAM                  |
| `gpuCount`                              | `int`                             | `getGPU()`                | Total Number of GPUs Detected            |
| `monitors`                              | `Display` struct Array            | `getDisplay()`            | Total Number of Monitors Detected        |
| `Display (width, height, refresh rate)` | `int, int, int`                   | *within `Display` struct* | Monitor Resolution and Refresh Rate      |
| `displayCount`                          | `int`                             | `getDisplay()`            | Total Number of Active Displays Detected |

## How Does it Work ?

WinBun64 uses a mix of WinAPI, Registry Query, `cpuid` and `DXGI` to get system information.
WinBun64 functions accepts a single parameter which is a pointer to a `WINBUN` struct (`WINBUN*`).
The variable of type `WINBUN` is passed by address, and each function populates it with corresponding system information.

### 🔹 WinAPI

The Windows API (WinAPI) is the native API provided by Microsoft to interact directly with the Operating System.

WinBun64 uses a handful of lightweight WinAPI calls to fetch system level details like hostname, uptime, locale, etc. Functions such as `GetTickCount64()`(uptime), `GetUserNameA()`(username) and `GetComputerNameA()`(hostname) are directly used to extract these information.

The `GetNativeSystemInfo()` function is used to extract CPU architecture.

For getting display resolution and refresh rate of each available display `EnumDisplayDevices()` and `EnumDisplaySettings()` are used.

### 🔹 Registry Query

Windows registry is a hierarchical database storing config data for OS and installed software.

WinBun64 queries specific registry keys to obtain necessary details like OS product name, version and build number.

It uses `RegOpenKeyExA()` and `RegQueryValueExA()` to read these keys safely from `HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion`, avoiding the complexity of manual registry access.

### 🔹 DXGI (DirectX Graphics Infrastructure)

DXGI is part of the DirectX family and provides API for Graphics and GPU related information.

WinBun64 uses `DXGI` interfaces like `IDXGIFactory1()` and `IDXGIAdapter1()` to fetch GPU information such as GPU names, VRAM size and total number of adapters.

### 🔹 CPUID

`cpuid` is a processor instruction that returns detailed information about the CPU such as its Brand, features, etc.

WinBun64 uses it to get the full CPU Brand String. Since it uses `cpuid` this limits WinBun64 to just x86 and x86_64 (AMD64) systems only.

---

### Why did I make it ?

Initially I thought of making it as a neofetch/fastfetch equivalent for Windows but after seeing how ridiculously hard it is to get simple system information on Windows I thought of turning this into a library that will help getting info on Windows, and I wanted to build something too so that was enough excuse to build it.

Windows itself was not made for transparency and hence is not at all dev friendly by any means (at least I see it that way). WinAPI or the Windows SDK in general is quite challenging piece of tech I have ever worked with. But...
this project taught me a lot and I mean a lot, this was the first time using low level APIs like `DXGI` and WinAPI and I also learned makefiles for building this project. Moreover, I learned about compiler flags such as `-I` and `-L`,  building a static library and shipping it with headers.

Though not a full blown library it is a cool side project if considered. Learned a lot and really loved making this project equally frustrating and fun.

---

## ℹ Credits, Tools and Additional Info

- I used [chatGPT](https://chatgpt.com/) for 99% of the time to learn about WinAPI, `DXGI`, Registry Query and the whole project. I preferred chatGPT over Microsoft Docs because it was in a more "understandable" language. With that said I didn't copy paste code I wrote what I understood.

- Other References - [Microsoft Docs](https://learn.microsoft.com/en-us/windows/win32/api/) (Yes I used it a bit), [Stack Overflow](https://stackoverflow.com/questions).

- WinBun64 used `cpuid` to get processor brand so it will not work on ARM - based Windows machines.

- Thanks to [Arpan](https://github.com/arpank01) for testing it out, helped me find bugs and issues.

- I will *try* to keep this library updated as needed alongside the documentation.
