#include "Column.h"
#include "DrawingFunctions.h"

Column::Column() {

}

void Column::render(int columnX, int columnY, int columnWidth, LPDIRECT3DDEVICE9 *pDevice, FontManager *fontManager) {
	int currPos = columnY;
	for (int i = 0; i < items.size(); i++) {
		MenuItem *mi = items[i].second;
		//drawFilledRect(columnX + mi->getPaddingX(), currPos + mi->getPaddingY(), columnWidth - mi->getPaddingX() * 2, mi->getHeight() - mi->getPaddingY()*2, 1, 0xffff671f, 0xff00ff00, pDevice);
		mi->render(columnX, currPos, columnWidth, pDevice, fontManager);
		currPos += mi->getHeight();
	}
}

void Column::handleInput(int columnX, int columnY, int columnWidth, int mouseX, int mouseY) {
	int currPos = columnY;
	for (int i = 0; i < items.size(); i++) {
		items[i].second->handleInput(columnX, currPos, columnWidth, mouseX, mouseY);
		currPos += items[i].second->getHeight();
	}
}
