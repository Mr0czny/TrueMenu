#pragma once
#include "MenuItem.h"

class Button : public MenuItem {
public:
	Button(const char* name);
	Button(const char* name, RECT margins);
	void render(int x, int y, int columnWidth, LPDIRECT3DDEVICE9 *pDevice, FontManager *fontManager);
	void handleInput(int x, int y, int columnWidth, int mouseX, int mouseY);
	int getHeight();

private:
	RECT margins;
	const char* name;
};
