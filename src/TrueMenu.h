#pragma once
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3d9.lib")

#include "FontManager.h"
#include "MenuPage.h"
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>

class TrueMenu {
public:
	TrueMenu(const char* name, int width, int height, LPDIRECT3DDEVICE9 *pDevice);
	void render(LPDIRECT3DDEVICE9 *pDevice);
	void handleInput(int mouseX, int mouseY);

	void addPage(const char* pageName, MenuPage* page) {
		pages.push_back(std::make_pair(pageName, page));
	}

	MenuPage* getPage(const char* colName) {
		for (int i = 0; i < pages.size(); i++) {
			if (pages[i].first == colName)
				return pages[i].second;
		}
		return NULL;
	}

	void setSelectedPage(const char* colName) {
		for (int i = 0; i < pages.size(); i++) {
			if (pages[i].first == colName)
				selectedPage = i;
		}
	}

private:
	std::vector<std::pair<const char*, MenuPage*>> pages;
	const char* name;
	int width, height;
	int posX = 100, posY = 100;
	FontManager* fontManager;
	int isBeingDragged = false;
	int mouseXoffset, mouseYoffset;
	int selectedPage = 0;
	bool drawMenu = true;
};