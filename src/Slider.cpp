#include "Slider.h"
#include "DrawingFunctions.h"
#include "LogicalHelper.h"
#include <math.h>

Slider::Slider(const char* name, RECT margins, float minValue, float maxValue, float step) : name(name), margins(margins), minValue(minValue), maxValue(maxValue), step(step) {

}

Slider::Slider(const char* name, RECT margins, float minValue, float maxValue, float step, float startValue) : name(name), margins(margins), minValue(minValue), maxValue(maxValue), step(step), startValue(startValue) {
	if (fmod(startValue,step) != 0) {
		startValue = startValue - fmod(startValue, step);
	}
	if (startValue < minValue) {
		startValue = minValue;
	}
	else if (startValue > maxValue) {
		startValue = maxValue;
	}
}

void Slider::render(int x, int y, int columnWidth, LPDIRECT3DDEVICE9 *pDevice, FontManager *fontManager) {
	RECT fontRect = GetTextRect(name, fontManager->font12);
	float width = columnWidth - margins.left - margins.right - 6;
	DrawString(x + margins.left + (columnWidth - margins.left - margins.right) / 2 - (fontRect.right - fontRect.left) / 2, y + getHeight() / 2 - (fontRect.bottom - fontRect.top) / 2, 0xFFFFFFFF, fontManager->font12, name);
	FillRGB(x + margins.left, y + margins.top + 15, width + 3, 5, 0xFF555555, pDevice);
	float steps = (maxValue - minValue) / step;
	float stepDistance = width / steps;
	drawFilledRect(x + margins.left + (startValue/step) * stepDistance, y + margins.top + 13, 6, 9, 1, 0xFF2E2E2E, 0xffffffff, pDevice);
}

void Slider::handleInput(int x, int y, int columnWidth, int mouseX, int mouseY) {
	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0) {
		if (isInRect(mouseX, mouseY, x + margins.left, y + margins.top + 13, columnWidth - margins.left - margins.right - 3, 9)) {
			mouseX = mouseX - x-3;
			float width = columnWidth - margins.left - margins.right - 6;
			float steps = (maxValue - minValue) / step;
			float stepDistance = width / steps;
			startValue = round((mouseX - margins.left) / stepDistance) * step;
			if (startValue < minValue) {
				startValue = minValue;
			}
			else if (startValue > maxValue) {
				startValue = maxValue;
			}
		}
	}
}

int Slider::getHeight() {
	return 25 + margins.top + margins.bottom;
}