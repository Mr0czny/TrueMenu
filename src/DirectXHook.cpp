#include "DirectXHook.h"
#include "TrueMenu.h"



LRESULT CALLBACK MsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { return DefWindowProc(hwnd, uMsg, wParam, lParam); }
TrueMenu* trueMenu;

typedef HRESULT(WINAPI* tEndScene)(LPDIRECT3DDEVICE9 pDevice);
tEndScene oEndScene;

HRESULT WINAPI hookedEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if(!trueMenu)
		trueMenu = new TrueMenu("Crockers", 500, 300, &pDevice);
	trueMenu->render(&pDevice);
	return oEndScene(pDevice);
}


DirectXHook::DirectXHook() {
	WNDCLASSEX wc = { sizeof(WNDCLASSEX),CS_CLASSDC,MsgProc,0L,0L,GetModuleHandle(NULL),NULL,NULL,NULL,NULL,"DX",NULL };
	RegisterClassEx(&wc);
	HWND hWnd = CreateWindow("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, GetDesktopWindow(), NULL, wc.hInstance, NULL);
	LPDIRECT3D9 pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	LPDIRECT3DDEVICE9 pd3dDevice;
	pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pd3dDevice);
	DWORD* pVTable = (DWORD*)pd3dDevice;
	pVTable = (DWORD*)pVTable[0];
	VTable[0] = pVTable[42]; //EndScene
	VTable[1] = pVTable[82]; //DrawIndexPrimitive
	VTable[2] = pVTable[100]; //SetStreamSource

	oEndScene = (tEndScene)DetourFunction((PBYTE)VTable[0], (PBYTE)hookedEndScene);

	DestroyWindow(hWnd);
}

void DirectXHook::inputHandler(int mouseX, int mouseY) {
	trueMenu->handleInput(mouseX, mouseY);
}
