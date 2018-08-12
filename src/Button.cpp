#include "Button.h"
#include "DrawingFunctions.h"


Button::Button(const char* name) : name(name) {

}

Button::Button(const char* name, RECT margins) : name(name), margins(margins){

}

void Button::render(int x, int y, int columnWidth, LPDIRECT3DDEVICE9 *pDevice, FontManager *fontManager) {
	drawFilledRect(x + margins.left, y + margins.top, columnWidth - margins.left - margins.right, getHeight() - margins.top - margins.bottom, 1, 0xFF2E2E2E, 0xFF555555, pDevice);
	RECT fontRect = GetTextRect(name, fontManager->font12);
	DrawString(x + margins.left + (columnWidth - margins.left - margins.right) / 2 - (fontRect.right - fontRect.left) / 2, y + getHeight() / 2 - (fontRect.bottom - fontRect.top) / 2, 0xFFFFFFFF, fontManager->font12, name);
}

void Button::handleInput(int x, int y, int columnWidth, int mouseX, int mouseY) {

}

int Button::getHeight() {
	return 20 + margins.top + margins.bottom;
}