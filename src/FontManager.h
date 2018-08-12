#pragma once

#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3d9.lib")

#include <d3d9.h>
#include <d3dx9.h>

class FontManager {
public:
	LPD3DXFONT font12;
	LPD3DXFONT font12Bold;
	LPD3DXFONT font14;
	FontManager(LPDIRECT3DDEVICE9 *pDevice);
};