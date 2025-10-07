#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "../headers/sysInfo.h"
#include "../headers/sysFunctions.h"

void getOS(sysInfo* system){
    HKEY hkey;
    char productName[64];
    char buildNumber[32];
    char versionNumber[8];

    DWORD productSize = sizeof(productName);
    DWORD buildSize = sizeof(buildNumber);
    DWORD versionSize = sizeof(versionNumber);

    //open registry key
    LONG stat = RegOpenKeyExA(
        HKEY_LOCAL_MACHINE,
        "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
        0,
        KEY_READ,
        &hkey
    );

    if(stat != ERROR_SUCCESS){
        printf("Error Getting OS Info...");
        return;
    }

    //query product name
    stat = RegQueryValueExA(
        hkey,
        "ProductName",
        NULL,
        NULL,
        (LPBYTE)productName,
        &productSize
    );

    if(stat != ERROR_SUCCESS){
        printf("Error Getting Product Name...");
        RegCloseKey(hkey);
        return;
    }

    //query version number
    stat = RegQueryValueExA(
        hkey,
        "DisplayVersion",
        NULL,
        NULL,
        (LPBYTE)versionNumber,
        &versionSize
    );

    if(stat != ERROR_SUCCESS){
        //query using an older value for older windows
        LONG nested_stat = RegQueryValueExA(
            hkey,
            "ReleaseId",
            NULL,
            NULL,
            (LPBYTE)versionNumber,
            &versionSize
        );

        if (nested_stat != ERROR_SUCCESS) {
            printf("Error Getting OS version...");
            RegCloseKey(hkey);
            return;
        }

    }

    //query build number
    stat = RegQueryValueExA(
        hkey,
        "CurrentBuild",
        NULL,
        NULL,
        (LPBYTE)buildNumber,
        &buildSize
    );

    if(stat != ERROR_SUCCESS){
        printf("Error Getting Product Name...");
        RegCloseKey(hkey);
        return;
    }

    memcpy(system->OS_ProductName, productName, 64);
    memcpy(system->OS_version, versionNumber, 8);
    memcpy(system->OS_buildNumber, buildNumber, 32);

    RegCloseKey(hkey);
}
