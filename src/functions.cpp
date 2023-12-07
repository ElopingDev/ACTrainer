#include "functions.h"

DWORD baseModule = 0;  // Define the variable
BYTE originalInstructions[4] = { 0 };  // Define the variable
BYTE recoilNop[] = { 0x90, 0x90, 0x90, 0x90 };  // Define the variable
DWORD recoilAddress = 0x004C2EC3 - baseModule;

void RestoreOriginalInstructions(DWORD destination, BYTE* originalInstructions, size_t size) {    // Check if the original instructions are valid (not empty)
    if (originalInstructions[0] != 0) {
        WriteProcessMemory(GetCurrentProcess(), (LPVOID)destination, originalInstructions, size, NULL);
    }
}
    DWORD GetPointerAddress(DWORD ptr, std::vector<DWORD> offsets)
    {
        DWORD addr = ptr;
        for (int i = 0; i < offsets.size(); ++i)
        {
            addr = *(DWORD*)addr;
            addr += offsets[i];
        }
        return addr;
    }

    DWORD Patch(BYTE * dst, BYTE * src, unsigned int size, HANDLE hProcess)
    {
        DWORD oldprotect;
        VirtualProtectEx(hProcess, dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
        WriteProcessMemory(hProcess, dst, src, size, nullptr);
        VirtualProtectEx(hProcess, dst, size, oldprotect, &oldprotect);
    }

    DWORD NopPatch(BYTE * dst, unsigned int size, HANDLE hProcess)
    {
        BYTE* nopArray = new BYTE[size];
        memset(nopArray, 0x90, size);

        Patch(dst, nopArray, size, hProcess);
        delete[] nopArray;

    }