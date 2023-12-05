#pragma once
#include <vector>
#include <Windows.h>
class Offsets
{
public:
	std::vector<DWORD> ammoOffsets = { 0x364, 0x14, 0x0 };
	std::vector<DWORD> yPosOffsets = { 0x30 };
};
