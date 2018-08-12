#include "MenuPage.h"
#include "DrawingFunctions.h"


MenuPage::MenuPage(int menuWidth, int menuHeight) : menuWidth(menuWidth), menuHeight(menuHeight){

}

void MenuPage::render(int menuPosX, int menuPosY, LPDIRECT3DDEVICE9 *pDevice, FontManager *fontManager) {
	float startingPos = menuPosX + 10;
	float allWidth = menuWidth - 20;
	float columnWidth = allWidth / columns.size();
	for (int i = 0; i < columns.size(); i++) {
		drawFilledRect(startingPos + columnWidth * i, menuPosY + 50, columnWidth, menuHeight - 60, 1, 0xffba671f, 0xff000000, pDevice);
		columns[i].second->render(startingPos + columnWidth * i, menuPosY + 50, columnWidth, pDevice, fontManager);
	}
}

void MenuPage::handleInput(int menuPosX, int menuPosY, int mouseX, int mouseY) {
	float startingPos = menuPosX + 10;
	float allWidth = menuWidth - 20;
	float columnWidth = allWidth / columns.size();
	for (int i = 0; i < columns.size(); i++) {
		columns[i].second->handleInput(startingPos + columnWidth * i, menuPosY + 50, columnWidth, mouseX, mouseY);
	}
}