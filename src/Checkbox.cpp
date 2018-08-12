#include "Checkbox.h"
#include "DrawingFunctions.h"
#include "logicalHelper.h"

Checkbox::Checkbox(const char* name) : name(name) {

}

Checkbox::Checkbox(const char* name, bool isSelected) : name(name), selected(selected) {

}

Checkbox::Checkbox(const char* name, RECT margins, bool isSelected): name(name), margins(margins), selected(selected) {

}

void Checkbox::render(int x, int y, int columnWidth, LPDIRECT3DDEVICE9 *pDevice, FontManager *fontManager) {
	if(selected)
		drawFilledRect(x + margins.left, y + margins.top, 10, getHeight() - margins.top - margins.bottom, 1, 0xFFFF9400, 0xFF2E2E2E, pDevice);
	else
		drawFilledRect(x + margins.left, y + margins.top, 10, getHeight() - margins.top - margins.bottom, 1, 0xFF44260C, 0xFF2E2E2E, pDevice);
	DrawString(x + margins.left + 12, y + margins.top-2, 0xFFFFFFFF, fontManager->font12, name);
}

void Checkbox::handleInput(int x, int y, int columnWidth, int mouseX, int mouseY) {
	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0) {
		isMousePressed = true;
	} else {
		if (isMousePressed) {
			isMousePressed = false;
			if(isInRect(mouseX, mouseY, x + margins.left, y + margins.top, 10, getHeight() - margins.top - margins.bottom)) {
				selected = !selected;
			}
		}
	}

}

int Checkbox::getHeight() {
	return 10 + margins.top + margins.bottom;
}