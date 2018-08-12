#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "FontManager.h"

class MenuItem {
public:
	//MenuItem();
	//MenuItem(int paddingX, int paddingY);
	virtual int getHeight() = 0;
	virtual void render(int x, int y, int width, LPDIRECT3DDEVICE9 *pDevice, FontManager *fontManager);
	virtual void handleInput(int x, int y, int columnWidth, int mouseX, int mouseY);
	
};