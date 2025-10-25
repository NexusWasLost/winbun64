# WinBun64

WinBun64 is a lightweight C library for fetching system information on Windows.

WinBun64 is written in C but is compatible with both C and C++.

## 🔺 Features

- Easy to use and lightweight Library to get System Information on Windows.
- Abstracts away complex parts like Registry Query, DXGI queries and other pain point in getting system info on a Windows machine.
- Compatible with both C and C++.
- Easy to understand naming for variables.
- Supports up to 4 display resolutions and 4 GPUs.
- Can be built from source to increase count of maximum displays and GPUs accounted for.
- Makefile included to help easily build from source.
- Fully supports both ANSI and wide-character (`wchar_t`) strings for compatibility across C and C++ projects.
- Uses only native Windows SDK components like WinAPI, Registry and DXGI.
- Modular code structure - Well structured headers and each function is wrapped in separate `.c` file.

## 💿 Supported Constraints

- *CPU Architectures:* x86 (32-bit) and x86_64 (64 bit, AMD64).

- *Maximum Monitor Resolutions:* 4.

- *Maximum GPUs:* 4.

- *Windows Version Tested:* Windows 11 and Windows 10 (may work on 7, 8, 8.1, Vista, XP; Not tested).

- *Compilers:* WinBun64 is compiled using [GCC (MinGW)](https://nuwen.net/mingw.html) so its fully supported; [Clang](https://clang.llvm.org/) should work (not tested); [MSVC](https://visualstudio.microsoft.com/vs/features/cplusplus/) **not supported** without changing source code and rebuild.

## 📦 Downloading the Library

WinBun64 is shipped as a static library (`.a`) alongside headers files in an "include" folder.

- `include/` - contains `winbun.h` and `winbun_functions.h`.
- `lib/` - contains `libwinbun.a` (the actual library).

To get started, download the library from [releases](https://github.com/NexusWasLost/winbun64/releases/) or click [here](https://github.com/NexusWasLost/winbun64/releases/download/v1.0/winbun64.zip) to start download.

***IMPORTANT:*** The path to both the headers and the library are required while linking as the compiler does not know where the include headers and the actual library exists and needs to be specified at the time of linking.

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

Each function fills the variable named `bun` with respective info.

Assuming the code file is called `main.c`, Compile using `gcc`:

```shell
gcc main.c -I"path-to-include-headers" -L"path-to-library" -l:libwinbun.a -ldxgi -ldxguid -lole32 -o main.exe
```

**IMPORTANT:** WinBun64 depends on Windows provided Libraries such as `dxgi`, `dxguid` and `ole32` as it uses `DXGI` for GPU information therefore these needs to be linked while producing an `exe`.

Additional info:
  1. The `-I` flag tells the compiler to check for include headers in the specified directory. The path to `winbun.h` and `winbun_functions.h` must be provided here.

  2. The `-L` flag tells the compiler to check for the library (`.a` file or `.lib` file) in the specified directory. The path to `libwinbun.a` must be provided here.

  3. The `-l:` is used to specify linking hence tells the compiler to link against the library `libwinbun.a`.


## 🔨 Building from Source

The library can be built from source if needed.

*Pre-requisites* : A C Compiler (GCC preferred, can also use Clang), make for makefiles.

1. Clone the repository

```shell
git clone https://github.com/NexusWasLost/winbun64.git
```

2. Navigate into the directory

```shell
cd winbun64
```

3. Make `.o` files and archive using make

```shell
make
```

This will output a static library and can be used alongside the headers anywhere.

### 🔸 **Building with MSVC**

I have never personally used MSVC so I am not sure on the compile and build commands but here are the source code changes needed to make it MSVC compatible.

In `cpu.c`, replace GCC specific - `<cpuid.h>` and `__get_cpuid()` with MSVC equivalents:

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

Then compile the source code files (`.c`) files into `.o` files and build a static library. The library extension will be `.lib` instead of `.a` when compiled using MSVC.

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

## ❔ How Does it Work ?

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

### 🍀 Why did I make it ?

Initially I thought of making it as a neofetch/fastfetch equivalent for windows but after seeing how ridiculously hard it is to get simple system information in Windows I thought of turning this into a library that will help me or others in the future to get system info on a stubborn OS such as Windows.

I made it as a cool and practical project that can help me (or others) to easily get system info on Windows system without going through the pain I did.

Windows itself was not made for transparency and hence is not at all dev friendly by any means. WinAPI or the Windows SDK in general is the worst piece of tech I have ever worked with. But...
this project taught me a lot and I mean a lot, this was the first time using low level APIs like `DXGI` and WinAPI and I also learned makefiles for building this project. Moreover, I learned about compiler flags such as `-I` and `-L`,  building a static library and shipping it with headers.

Really loved making this project equally frustrating and fun.

---

## ℹ Credits, Tools and Additional Info

- I used [chatGPT](https://chatgpt.com/) for 99% of the time to learn about WinAPI, `DXGI`, Registry Query and the whole project. I preferred chatGPT over Microsoft Docs because it was in a more "understandable" language. With that said I didn't copy paste code I wrote what I understood.

- Other References - [Microsoft Docs](https://learn.microsoft.com/en-us/windows/win32/api/) (Yes I used it a bit), [Stack Overflow](https://stackoverflow.com/questions).

- WinBun64 used `cpuid` to get processor brand so it will not work on ARM - based Windows machines.

- Thanks to [Arpan](https://github.com/arpank01) for running a `.exe` that uses this library, helped me find bugs and issues.

- I will try to keep this library updated as needed alongside the documentation.

- All the Blank links will be filled soon and this bullet point will be removed.
