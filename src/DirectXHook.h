#pragma once
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3d9.lib")

#include <d3d9.h>
#include <d3dx9.h>
#include <detours.h>

class DirectXHook {
public:
	DirectXHook();
	void inputHandler(int mouseX, int mouseY);

private:
	DWORD VTable[3] = {0};

};