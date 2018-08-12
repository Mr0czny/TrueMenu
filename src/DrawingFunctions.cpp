#include "DrawingFunctions.h"
#pragma warning(disable:4996)

void DrawString(int x, int y, DWORD color, LPD3DXFONT font, const char *fmt, ...)
{
	RECT FontPos = { x, y, x + 120, y + 16 };
	char buf[1024] = { '\0' };
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf(buf, fmt, va_alist);
	va_end(va_alist);

	font->DrawText(NULL, buf, -1, &FontPos, DT_NOCLIP, color);
}

void FillRGB(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 *pDevice)
{
	static ID3DXLine* pLine;

	if (!pLine)
		D3DXCreateLine(*pDevice, &pLine);

	D3DXVECTOR2 vLine[2];

	pLine->SetWidth(w);
	pLine->SetAntialias(false);
	pLine->SetGLLines(false);

	vLine[0].x = x + w / 2;
	vLine[0].y = y;
	vLine[1].x = x + w / 2;
	vLine[1].y = y + h;

	pLine->Begin();
	pLine->Draw(vLine, 2, Color);
	pLine->End();
}

void drawEmptyRect(int x1, int y1, int x2, int y2, int width, D3DCOLOR color, LPDIRECT3DDEVICE9 *pDevice) {
	drawLine(D3DXVECTOR2(x1, y1), D3DXVECTOR2(x2, y1), width, false, color, pDevice);
	drawLine(D3DXVECTOR2(x1, y1), D3DXVECTOR2(x1, y2), width, false, color, pDevice);
	drawLine(D3DXVECTOR2(x2, y1), D3DXVECTOR2(x2, y2), width, false, color, pDevice);
	drawLine(D3DXVECTOR2(x1, y2), D3DXVECTOR2(x2, y2), width, false, color, pDevice);
}

void drawFilledRect(int x, int y, int width, int height, int borderWidth, D3DCOLOR fillingColor, D3DCOLOR borderColor, LPDIRECT3DDEVICE9 *pDevice) {
	FillRGB(x, y, width, height, borderColor, pDevice);
	FillRGB(x + borderWidth, y + borderWidth, width - 2 * borderWidth, height - 2 * borderWidth, fillingColor, pDevice);
}

int GetTextWidth(const char *szText, LPD3DXFONT pFont)
{
	RECT rcRect = { 0,0,0,0 };
	if (pFont)
	{
		pFont->DrawText(NULL, szText, strlen(szText), &rcRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
	}

	return rcRect.right - rcRect.left;
}

RECT GetTextRect(const char *szText, LPD3DXFONT pFont)
{
	RECT rcRect = { 0,0,0,0 };
	if (pFont)
	{
		pFont->DrawText(NULL, szText, strlen(szText), &rcRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
	}

	return rcRect;
}

void drawLine(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float width, bool antialias, DWORD color, LPDIRECT3DDEVICE9 *pDevice)
{
	static ID3DXLine* mLine;

	if (!mLine) {
		D3DXCreateLine(*pDevice, &mLine);
		mLine->SetAntialias(0);
	}

	D3DXVECTOR2 line[] = { pos1, pos2 };
	mLine->SetWidth(width);
	mLine->Begin();
	mLine->Draw(line, 2, color);
	mLine->End();
}