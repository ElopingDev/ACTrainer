#pragma once
#include <vector>
#include <Windows.h>

extern DWORD baseModule;  // Declare as extern
extern BYTE originalInstructions[4];  // Declare as extern
extern BYTE recoilNop[4];  // Declare as extern
extern DWORD recoilAddress;

void RestoreOriginalInstructions(DWORD destination, BYTE* originalInstructions, size_t size);

DWORD GetPointerAddress(DWORD ptr, std::vector<DWORD> offsets);


DWORD Patch(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);


DWORD NopPatch(BYTE* dst, unsigned int size, HANDLE hProcess);


