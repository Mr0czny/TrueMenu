#pragma once
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3d9.lib")

#include "Column.h"
#include "FontManager.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

class MenuPage {
public:
	MenuPage(int menuWidth, int menuHeight);
	void render(int menuPosX, int menuPosY, LPDIRECT3DDEVICE9 *pDevice, FontManager *fontManager);
	void handleInput(int menuPosX, int menuPosY, int mouseX, int mouseY);

	void addColumn(const char* colName, Column *column) {
		columns.push_back(std::make_pair(colName, column));
	}

	Column* getColumn(const char* colName) {
		for (int i = 0; i < columns.size(); i++) {
			if (columns[i].first == colName)
				return columns[i].second;
		}
		return NULL;
	}

private:
	int menuWidth;
	int menuHeight;
	std::vector<std::pair<const char*, Column*>> columns;
};