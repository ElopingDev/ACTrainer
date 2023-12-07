#pragma once
#include <d3d9.h>
#include <vector>
#include "functions.h"


namespace gui
{
	// window size
	constexpr int WIDTH = 500;
	constexpr int HEIGHT = 300;

	inline bool exit = true;

	//winapi window vars
	inline HWND window = nullptr;
	inline WNDCLASSEXA windowClass = { };

	// points for window movement
	inline POINTS position = { };

	// directx state vars
	inline PDIRECT3D9 d3d = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS presentParameters = { };

	void CreateHWindow(const char* windowName, const char* className) noexcept;
	void DestroyHWindow() noexcept;

	bool CreateDevice() noexcept;
	void ResetDevice() noexcept;
	void DestroyDevice() noexcept;

	void CreateImGui() noexcept;
	void DestroyImGui() noexcept;

	void BeginRender() noexcept;
	void EndRender() noexcept;
	void Render() noexcept;
}

namespace hacks
{
	inline bool ammo = false;
	inline bool flyHack = false;
	inline bool wRecoil = false;

}

class Offsets
{
public:
	std::vector<DWORD> ammoOffsets = { 0x364, 0x14, 0x0 };
	std::vector<DWORD> yPosOffsets = { 0x30 };
	std::vector<DWORD> wRecoilOffsets = { 0x365, 0xC, 0x60 };
	DWORD baseAddress = 0x017E0A8;
	DWORD baseModule = (DWORD)GetModuleHandle("ac_client.exe");
	DWORD recoilAddress = 0x004C2EC3 - baseModule;


};