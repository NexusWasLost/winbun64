# Lumi

Lumi is a lightweight C library for fetching system information on Windows.

Lumi is written in C and compatible with C++ aswell.

## Supported Constraints

- *CPU Architectures:* x86_64 (64 bit, AMD64), should work on x86 (32  bit systems; Not tested).

- *Maximum Monitor Resolutions:* 4.

- *Maximum GPUs:* 4.

- *Windows Version Tested:* Windows 11 and Windows 10 (may work on 7, 8, 8.1, Vista, XP; Not tested).

- *Compilers:* Lumi is compiled using [GCC (MinGW)](https://nuwen.net/mingw.html) so its fully supported; [Clang](https://clang.llvm.org/) should work (not tested); [MSVC](https://visualstudio.microsoft.com/vs/features/cplusplus/) **not supported** without changing source code and rebuild.

## Downloading the Library

Lumi is shipped as a static library (`.a`) alongside headers files in an "include" folder.

- `include/` - contains `lumi.h` and `lumi_functions.h`.
- `lib/` - contains `liblumi.a` (the actual library).

Download the library from [releases](https://github.com/NexusWasLost/Lumi/releases/).

## Example Code

```c
#include <stdio.h>
#include "lumi.h"
#include "lumi_functions.h"

int main(){
	LUMI lumi; //define a LUMI variable

	printf("Version: ");
	printf(__LUMI_VERSION);
	printf("\n");

	getCPU(&lumi); //call needed function
	getMemory(&lumi);
	getDisplay(&lumi);
	getNetwork(&lumi);

	//print the info
	printf("CPU: %s\n", lumi.CPU);
	printf("RAM: %llu MB / %llu MB\n", lumi.usedMemory, lumi.totalMemory);

	//print all active displays.
	for(int x = 0; x < lumi.displayCount; x++){
		printf("Display %d: %d x %d @ %d Hz\n",
		 x + 1,
		 lumi.monitors[x].width, lumi.monitors[x].height, lumi.monitors[x].refreshRate
		);
	}

	return 0;
}
```

Each function populates a struct variable named `lumi` with respective info.

Assuming the code file is called `main.c`, Compile using `gcc`:

```shell
gcc main.c -o main.exe -I"path-to-include-headers" -L"path-to-library" -llumi -ldxgi -ldxguid -lole32 -liphlpapi
```

## Building from Source

The library can be built from source if needed.

*Compiler:* GCC or Clang Toolchain and CMake.

1. Clone the repository

```shell
git clone https://github.com/NexusWasLost/lumi.git
```

2. Navigate into the directory

```shell
cd lumi
```

### Build using CMake

1. Initialize CMake
```shell
cmake -B build -G "MinGW Makefiles"
```

2. Build the library (CMake creates it in build directory)
```shell
cmake --build build
```

---

### 🔸 **Building with MSVC**

(Not Tested) In `cpu.c`, replace GCC specific - `<cpuid.h>` and `__get_cpuid()` with MSVC equivalents:

```c
...
#include <intrin.h> //include intrin.h instead of cpuid.h
...
void getCPU(LUMI* lumi){
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

## List of Fields and Functions

| Field                                      | Type                              | Function                                                                                 | Description                              |
| ------------------------------------------ | --------------------------------- | ---------------------------------------------------------------------------------------- | ---------------------------------------- |
| `CPU`                                      | `char[]`                          | `getCPU()`                                                                               | CPU Brand String                         |
| `CPU_Architecture`                         | `char[]`                          | `getCPU()`                                                                               | CPU Architecture                         |
| `OS_ProductName`                           | `char[]`                          | `getOS()`                                                                                | Windows Product Name                     |
| `OS_version`                               | `char[]`                          | `getOS()`                                                                                | OS version String                        |
| `OS_buildNumber`                           | `char[]`                          | `getOS()`                                                                                | Windows Build Number                     |
| `host`                                     | `char[]`                          | `getHostName()`                                                                          | Computer Hostname                        |
| `locale`                                   | `wchar_t[]`                       | `getLocale()`                                                                            | System Locale                            |
| `currentUserName`                          | `char[]`                          | `getCurrentUsername()`                                                                   | Logged in username                       |
| `totalMemory`                              | `unsigned long long`              | `getMemory()`                                                                            | Total Physical Memory (in MB)            |
| `availableMemory`                          | `unsigned long long`              | `getMemory()`                                                                            | Total Available Memory (in MB)           |
| `usedMemory`                               | `unsigned long long`              | `getMemory()`                                                                            | Total Used Memory (in MB)                |
| `memoryLoad`                               | `unsigned long long`              | `getMemory()`                                                                            | Current Memory Load (Percentage)         |
| `uptime`                                   | `unsigned long long`              | `getUptime()`                                                                            | System Uptime (in seconds)               |
| `gpu`                                      | `GPU[]`                           | `getGPU()`                                                                               | List of GPUs Detected                    |
| `GPU_Name`, `totalVRAM`                    | `wchar_t[]`, `unsigned long long` | *calling `getGPU()` automatically populates these 2 fields for each GPU*                 | GPU Name and total VRAM                  |
| `gpuCount`                                 | `size_t`                             | `getGPU()`                                                                               | Total Number of GPUs Detected            |
| `monitors`                                 | `Display[]`                       | `getDisplay()`                                                                           | Total Number of Monitors Detected        |
| `width`, `height`, `refreshRate`           | `int, int, int`                   | *calling `getDisplay()` automatically populates these 3 fields for each monitor*         | Monitor Resolution and Refresh Rate      |
| `displayCount`                             | `size_t`                             | `getDisplay()`                                                                           | Total Number of Active Displays Detected |
| `net_adapters`                             | `networkAdapter[]`                | `getNetwork()`                                                                           | List of active network adapters          |
| `networkAdapterName`, `networkAdapterDesc` | `wchar_t[]`, `wchar_t[]`          | *calling `getNetwork()` automatically populates these 2 fields for each network adapter* | Network Adapter Name and Description     |
| `networkAdapterCount`                      | `size_t`                          | `getNetwork()`                                                                           | Number of active network adapters        |

Each function called once will populate every field related to that particular function. For example `getCPU()` will populate `CPU` and `CPU Architecture` field with just one call. Fields that can have multiple data for example GPU and Network Adapters follow the same rule.

### Units

| Field                        | Unit      |
| ---------------------------- | --------- |
| `uptime`                     | Seconds   |
| `memory`                     | MB        |
| `VRAM`                       | MB        |
| Display `width` and `height` | Pixels    |
| Display `refreshRate`        | Hz        |


## How Does it Work ?

Lumi uses a mix of WinAPI, Registry Query, `cpuid` and `DXGI` to get system information.
Lumi functions accepts a single parameter which is a pointer to a `LUMI` struct (`LUMI*`).
The variable of type `LUMI` is passed by address, and each function populates it with corresponding system information.

### 🔹 WinAPI

The Windows API (WinAPI) is the native API provided by Microsoft to interact directly with the Operating System.

Lumi uses a handful of lightweight WinAPI calls to fetch system level details like hostname, uptime, locale, etc. Functions such as `GetTickCount64()`(uptime), `GetUserNameA()`(username) and `GetComputerNameA()`(hostname) are directly used to extract these information.

The `GetNativeSystemInfo()` function is used to extract CPU architecture.

For getting display resolution and refresh rate of each available display `EnumDisplayDevices()` and `EnumDisplaySettings()` are used.

### 🔹 Registry Query

Windows registry is a hierarchical database storing config data for OS and installed software.

Lumi queries specific registry keys to obtain necessary details like OS product name, version and build number.

It uses `RegOpenKeyExA()` and `RegQueryValueExA()` to read these keys safely from `HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion`, avoiding the complexity of manual registry access.

### 🔹 DXGI (DirectX Graphics Infrastructure)

DXGI is part of the DirectX family and provides API for Graphics and GPU related information.

Lumi uses `DXGI` interfaces like `IDXGIFactory1()` and `IDXGIAdapter1()` to fetch GPU information such as GPU names, VRAM size and total number of adapters.

### 🔹 CPUID

`cpuid` is a processor instruction that returns detailed information about the CPU such as its Brand, features, etc.

Lumi uses it to get the full CPU Brand String. Since it uses `cpuid` this limits Lumi to just x86 and x86_64 (AMD64) systems only.

---

### Why did I make it ?

Initially I thought of making it as a neofetch/fastfetch equivalent for Windows but after seeing how ridiculously hard it is to get simple system information on Windows I thought of turning this into a library that will help getting info on Windows, and I wanted to build something too so that was enough excuse to build it.

Windows itself was not made for transparency and hence is not at all dev friendly by any means (at least I see it that way). WinAPI or the Windows SDK in general is quite challenging piece of tech I have ever worked with. But...
this project taught me a lot and I mean a lot, this was the first time using low level APIs like `DXGI` and WinAPI and I also learned makefiles for building this project. Moreover, I learned about compiler flags such as `-I` and `-L`,  building a static library and shipping it with headers.

Though not a full blown library it is a cool side project if considered. Learned a lot and really loved making this project equally frustrating and fun.

---

## References

- WinAPI reference: [https://learn.microsoft.com/en-us/windows/win32/api/](https://learn.microsoft.com/en-us/windows/win32/api/)

- Network related API: [https://learn.microsoft.com/en-us/windows/win32/api/iptypes/ns-iptypes-ip_adapter_addresses_lh](https://learn.microsoft.com/en-us/windows/win32/api/iptypes/ns-iptypes-ip_adapter_addresses_lh)

- `swprintf`: [https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/sprintf-sprintf-l-swprintf-swprintf-l-swprintf-l?view=msvc-170](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/sprintf-sprintf-l-swprintf-swprintf-l-swprintf-l?view=msvc-170)

- Stack Overflow: [https://stackoverflow.com/questions](https://stackoverflow.com/questions)

## Additional Info

- Lumi used `cpuid` to get processor brand so it will not work on ARM - based Windows machines.

- I did AI-assisted coding to learn about WinAPI, `DXGI`, Registry Query and the whole project. I preferred AI  over MS Docs in many cases because it was easier to understand the stuff. With that said I didn't copy paste code, I wrote what I understood.

- I will *try* to keep this library updated as needed alongside the documentation.

## Credits

- Thanks to [Arpan](https://github.com/arpank01) for testing it out, helped me find bugs and issues.
