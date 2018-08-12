#include "TrueMenu.h"
#include "DrawingFunctions.h"
#include "LogicalHelper.h"
#include "Button.h"
#include "Slider.h"
#include "Checkbox.h"

TrueMenu::TrueMenu(const char* name, int width, int height, LPDIRECT3DDEVICE9 *pDevice) : name(name), width(width), height(height) {
	fontManager = new FontManager(pDevice);
	
	MenuPage* pg = new MenuPage(width, height);
	pg->addColumn("Toggles", new Column());
	Column* col = new Column();
	col->addMenuItem("LOL", new Button("Super Button", {0,0,0,0}));
	pg->addColumn("Aiming", col);
	col = new Column();
	col->addMenuItem("LOL", new Button("Tez tak mam", { 20,0,0,0 }));
	col->addMenuItem("LOL", new Button("Co to kurwa jest?", { 0,0,20,0 }));
	col->addMenuItem("Slider", new Slider("Speed", { 5,10,5,0 }, 0, 10, 0.25, 0));
	col->addMenuItem("Slider", new Slider("Speed2", { 5,10,5,0 }, 0, 10, 1, 0));
	col->addMenuItem("Slider", new Checkbox("WH", { 5,5,5,0 }, false));
	col->addMenuItem("Slider", new Checkbox("SpeedHack", { 5,5,5,0 }, false));
	col->addMenuItem("Slider", new Checkbox("Chujwie", { 5,5,5,0 }, false));
	pg->addColumn("Aimings", col);
	addPage("WallHack", pg);

	pg = new MenuPage(width, height);
	col = new Column();
	col->addMenuItem("LOL", new Button("chuj XD œæ", { 0,0,0,0 }));
	pg->addColumn("Aiming", col);
	pg->addColumn("Toggles", new Column());
	addPage("Aimbot", pg);
	
	pg = new MenuPage(width, height);
	col = new Column();
	col->addMenuItem("LOL", new Button("LOLLOLOLO", { 0,0,0,0 }));
	col->addMenuItem("Slider", new Slider("Speed", { 5,10,5,0 }, 0, 10, 0.25, 0));
	pg->addColumn("Aiming", col);
	addPage("DarkRp", pg);

	pg = new MenuPage(width, height);
	col = new Column();
	col->addMenuItem("LOL", new Button("LOL", { 0,0,0,0 }));
	col->addMenuItem("LOL", new Button("LOL", { 0,0,0,0 }));
	pg->addColumn("Aiming", col);
	addPage("ETC", pg);


	setSelectedPage("WallHack");

}

void TrueMenu::render(LPDIRECT3DDEVICE9 *pDevice) {
	if (drawMenu) {
		FillRGB(posX, posY, width, height, 0xFF000000, pDevice);
		FillRGB(posX, posY + 24, width, height - 24, 0xFF444444, pDevice);
		FillRGB(posX, posY + 40, width, height - 40, 0xFFff8514, pDevice);
		DrawString(posX + 5, posY + 5, 0xFFFFFFFF, fontManager->font14, name);
		int pages_size = pages.size();
		for (int i = 0; i < pages.size(); i++) {
			MenuPage *page = pages[i].second;
			float distance = (float)width / (pages_size * 2);
			if (i == selectedPage) {
				FillRGB(posX + distance * ((i * 2)), posY + 24, distance * 2, 16, 0xFFff8514, pDevice);
				DrawString(posX + distance * ((i * 2) + 1) - GetTextWidth(pages[i].first, fontManager->font12Bold) / 2, posY + 25, 0xFF000000, fontManager->font12Bold, pages[i].first);
				page->render(posX, posY, pDevice, fontManager);
			}
			else {
				DrawString(posX + distance * ((i * 2) + 1) - GetTextWidth(pages[i].first, fontManager->font12) / 2, posY + 25, 0xFFFFFFFF, fontManager->font12, pages[i].first);
			}
		}
	}
}

void TrueMenu::handleInput(int mouseX, int mouseY) {
	if (GetKeyState(VK_INSERT) & 0x800) {
		drawMenu = !drawMenu;
		Sleep(150);
	}
	if (drawMenu) {
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0) {
			if (!isBeingDragged) {
				if (isInRect(mouseX, mouseY, posX, posY + 24, width, 16)) {
					float distance = width / pages.size();
					for (int i = 0; i < pages.size(); i++) {
						if (isInRect(mouseX, mouseY, posX + distance * i, posY + 24, distance, 16)) {
							selectedPage = i;
						}
					}
				}
				if (isInRect(mouseX, mouseY, posX, posY, width, 24)) {
					isBeingDragged = true;
					mouseXoffset = mouseX - posX;
					mouseYoffset = mouseY - posY;
				}
			}
			else {
				posX = mouseX - mouseXoffset;
				posY = mouseY - mouseYoffset;
			}
		}
		else {
			isBeingDragged = false;
		}
		if (!isBeingDragged) {
			pages[selectedPage].second->handleInput(posX, posY, mouseX, mouseY);
		}
	}

}