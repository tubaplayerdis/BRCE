#pragma once
#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

namespace menu
{
	inline Present oPresent;
	void initializeImGui();
	HRESULT __stdcall renderLoop(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
}