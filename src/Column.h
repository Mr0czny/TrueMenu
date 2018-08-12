#pragma once
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3d9.lib")

#include "MenuItem.h"
#include "FontManager.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

class Column {
public:
	Column();
	void render(int columnX, int columnY, int columnWidth, LPDIRECT3DDEVICE9 *pDevice, FontManager *fontManager);
	void handleInput(int columnX, int columnY, int columnWidth, int mouseX, int mouseY);

	void addMenuItem(const char* itemName, MenuItem* menuItem) {
		items.push_back(std::make_pair(itemName, menuItem));
	}

	MenuItem* getMenuItem(const char* itemName) {
		for (int i = 0; i < items.size(); i++) {
			if (items[i].first == itemName)
				return items[i].second;
		}
		return NULL;
	}

private:
	std::vector<std::pair<const char*, MenuItem*>> items;
};