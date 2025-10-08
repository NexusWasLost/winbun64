#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "../headers/sysInfo.h"
#include "../headers/sysFunctions.h"

void setOSProductName(int majorBuildNumber, sysInfo* system, char* productName){
    if(majorBuildNumber >= 22000){
        //The string "Windows 11" is total 10 chars + 1 char ('\0') and we store it in an array.
        //Copy the 12 bytes and the last one 11th index is '\0'.
        //The 11th index in the productName array is the space after major windows number and we overwrite previous null terminator and continue to append from the space.
        char win11[12] = "Windows 11";
        memcpy(system->OS_ProductName, win11, 12);
        memcpy(system->OS_ProductName + 11, productName + 11, OS_PRODUCT_NAME_SIZE - 11);
    }
    else{
        memcpy(system->OS_ProductName, productName, OS_PRODUCT_NAME_SIZE);
    }
}

void setOSVersion(sysInfo* system, char* versionNumber){
    memcpy(system->OS_version, versionNumber, OS_VERSION_SIZE);
}

void setOSBuildNumber(sysInfo* system, char* buildNumber){
    memcpy(system->OS_buildNumber, buildNumber, OS_BUILD_NUMBER_SIZE);
}

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

    //check major build for windows 11
    int major = atoi(buildNumber);
    setOSProductName(major, system, productName);
    setOSVersion(system, versionNumber);
    setOSBuildNumber(system, buildNumber);

    system->OS_ProductName[63] = '\0';
    system->OS_buildNumber[31] = '\0';
    system->OS_version[7] = '\0';

    RegCloseKey(hkey);
}
