// dllmain.cpp : Defines the entry point for the DLL application.
#pragma once

#include <Windows.h>
#include <iostream>
#include <WinUser.h>
#include <memoryapi.h>
#include <vector>
#include "functions.h"
#include "gui.h"


// Add this macro to enable more detailed logging during debugging
   


   DWORD WINAPI MainThread(HMODULE hModule) {
    Offsets offsets;
    int value;
    BYTE recoilNop[] = { 0x90, 0x90, 0x90, 0x90 };  // NOP instruction
    bool recoilSet = false;

    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Injected" << std::endl;
    gui::CreateHWindow("ACTrainer", "ACTrainer Class");
    gui::CreateDevice();
    gui::CreateImGui();
    std::cout << "ImGui Done" << std::endl;


    HANDLE hProcess = GetCurrentProcess();
    while (!GetAsyncKeyState(VK_END))
    {
        gui::BeginRender();
        gui::Render();
        gui::EndRender();
        
        Sleep(100);
        if (hacks::ammo == true)

        {
            int* ammo = (int*)GetPointerAddress(offsets.baseModule + 0x17E0A8, offsets.ammoOffsets);
            *ammo = 999;
        }

        if (hacks::wRecoil == true && recoilSet == false)
        {
            std::cout << "Attempting to read" << std::endl;
            ReadProcessMemory(GetCurrentProcess(), (LPVOID)(offsets.baseModule + offsets.recoilAddress), originalInstructions, sizeof(originalInstructions), NULL);
            std::cout << "READ" << std::endl;
            std::cout << "Attempting to WRITE" << std::endl;
            WriteProcessMemory(GetCurrentProcess(), (LPVOID)(offsets.baseModule + offsets.recoilAddress), recoilNop, sizeof(recoilNop), NULL);
            std::cout << "WROTE" << std::endl;
            recoilSet = true;
        }
        
        if (hacks::wRecoil == false && recoilSet == true)
        {
            RestoreOriginalInstructions(offsets.baseModule + offsets.recoilAddress, originalInstructions, sizeof(originalInstructions));
            recoilSet = false;
        }
       
    }
    
   // MessageBoxA(NULL, "Successfully uninjected.", "ACTrainer", NULL);
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
       // MessageBoxA(NULL, "ACTrainer Injected", "Injection", NULL);
    }
    return TRUE;
}
