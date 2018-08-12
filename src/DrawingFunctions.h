#pragma once
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3d9.lib")

#include <d3d9.h>
#include <d3dx9.h>
#include <string>


void DrawString(int x, int y, DWORD color, LPD3DXFONT font, const char *fmt, ...);

void FillRGB(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 *pDevice);

int GetTextWidth(const char *szText, LPD3DXFONT pFont);

RECT GetTextRect(const char *szText, LPD3DXFONT pFont);

void drawLine(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float width, bool antialias, DWORD color, LPDIRECT3DDEVICE9 *pDevice);

void drawEmptyRect(int x1, int y1, int x2, int y2, int width, D3DCOLOR color, LPDIRECT3DDEVICE9 *pDevice);

void drawFilledRect(int x, int y, int width, int height, int borderWidth, D3DCOLOR fillingColor, D3DCOLOR borderColor, LPDIRECT3DDEVICE9 *pDevice);
