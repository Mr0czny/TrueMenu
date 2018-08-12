#pragma once
#include "MenuItem.h"

class Checkbox : public MenuItem {
public:
	Checkbox(const char* name);
	Checkbox(const char* name, bool isSelected);
	Checkbox(const char* name, RECT margins, bool isSelected);
	void render(int x, int y, int columnWidth, LPDIRECT3DDEVICE9 *pDevice, FontManager *fontManager);
	void handleInput(int x, int y, int columnWidth, int mouseX, int mouseY);
	int getHeight();
	bool isSelected() {
		return selected;
	}

private:
	RECT margins;
	const char* name;
	bool selected;
	bool isMousePressed = false;
};
