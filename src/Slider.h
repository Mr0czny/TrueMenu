#pragma once
#include "MenuItem.h"

class Slider : public MenuItem {
public:
	Slider(const char* name, RECT margins, float minValue, float maxValue, float step);
	Slider(const char* name, RECT margins, float minValue, float maxValue, float step, float startValue);
	void render(int x, int y, int columnWidth, LPDIRECT3DDEVICE9 *pDevice, FontManager *fontManager);
	void handleInput(int x, int y, int columnWidth, int mouseX, int mouseY);
	int getHeight();
	float getValue() {
		return startValue;
	};

private:
	RECT margins;
	const char* name;
	float minValue, maxValue, step, startValue = minValue;
};
