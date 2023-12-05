// dllmain.cpp : Defines the entry point for the DLL application.
#pragma once

#include <Windows.h>
#include <iostream>
#include <WinUser.h>
#include <memoryapi.h>
#include <vector>
#include "functions.h"
#include "offsets.h"
#include "gui.h"


// Add this macro to enable more detailed logging during debugging
int value;
DWORD baseAddress = 0x017E0A8;


DWORD WINAPI MainThread(HMODULE hModule) {

   DWORD baseModule = (DWORD)GetModuleHandle("ac_client.exe");
   Offsets offsets;

    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Injected";
    gui::CreateHWindow("ACTrainer", "ACTrainer Class");
    gui::CreateDevice();
    gui::CreateImGui();
    std::cout << "ImGui Done";
  
    HANDLE hProcess = GetCurrentProcess();

    while (!GetAsyncKeyState(VK_END))
    {
        gui::BeginRender();
        gui::Render();
        gui::EndRender();

       Sleep(100);
        std::cout << hacks::ammo;
        if (hacks::ammo == true)
        {
            int* ammo = (int*)GetPointerAddress(baseModule + 0x17E0A8, offsets.ammoOffsets);
            *ammo = 999;
        }

    }
    
    MessageBoxA(NULL, "Successfully uninjected.", "ACTrainer", NULL);
    fclose(f);
    FreeConsole();
    gui::DestroyImGui();
    gui::DestroyDevice();
    gui::DestroyHWindow();
    FreeLibraryAndExitThread(hModule, 0);
    
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, NULL);
        MessageBoxA(NULL, "ACTrainer Injected", "Injection", NULL);
    }
    return TRUE;
}
