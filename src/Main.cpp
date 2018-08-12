#include <windows.h>
#include "DirectXHook.h"
#include <iostream>

HWND mainHwnd;
RECT clientRect, windowRect;

int width, height;

DirectXHook *directXHook;


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	//char class_name[80];
	char title[80];
	//GetClassName(hwnd, class_name, sizeof(class_name));
	GetWindowText(hwnd, title, sizeof(title));
	if (5 <= strlen(title) && (strncmp("Direc", title, 5) == 0)) {
		mainHwnd = hwnd;
		return FALSE;
	}
	return TRUE;
}

DWORD WINAPI initEverything(LPVOID) {
	directXHook = new DirectXHook();
	return TRUE;
};

DWORD WINAPI inputHandler(LPVOID) {
	while (true) {
		POINT p;
		if (GetCursorPos(&p))
		{
			GetClientRect(mainHwnd, &clientRect);
			GetWindowRect(mainHwnd, &windowRect);
			int windowWidth = windowRect.right - windowRect.left;
			int windowHeight = windowRect.bottom - windowRect.top;
			int sideBorder = (windowWidth - clientRect.right) / 2;
			int upperBorder = windowHeight - clientRect.bottom - sideBorder;

			int mouseX = p.x - (windowRect.left + sideBorder);
			int mouseY = p.y - (windowRect.top + upperBorder);
				

			if (mouseX < clientRect.right && mouseX >= 0 && mouseY < clientRect.bottom && mouseY >= 0) {
				directXHook->inputHandler(mouseX, mouseY);
			}
		}
		Sleep(1);
	}

	return TRUE;
}


BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpvReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		/*AllocConsole();
		AttachConsole(GetCurrentProcessId());
		freopen("CON", "w", stdout);*/
		EnumWindows(EnumWindowsProc, NULL);
		CreateThread(0, 0, initEverything, 0, 0, 0);
		CreateThread(0, 0, inputHandler, 0, 0, 0);
	}
	return TRUE;
}