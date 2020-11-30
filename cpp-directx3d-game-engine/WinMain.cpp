#include <Windows.h>
#include <sstream>
#include <string>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_CHAR:
	{
		static std::wstring title;
		title.push_back((char) wParam);

		SetWindowText(hWnd, title.c_str());
	}
	break;
	case WM_LBUTTONDOWN:
	{
		POINTS pt = MAKEPOINTS(lParam);
		std::wostringstream wss;

		wss << "(" << pt.x << ", " << pt.y << ")";

		SetWindowText(hWnd, wss.str().c_str());
	}
	break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow
) {

	// register window class
	const wchar_t className[] = L"Main window";

	WNDCLASSEX wc = { 0 };

	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = className;
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);

	// create instance of window
	HWND hWnd = CreateWindowEx(
		0,
		className,
		L"My first Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200,
		200,
		640,
		480,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	if (hWnd == nullptr) return 0;

	ShowWindow(hWnd, nCmdShow);

	// message loop
	MSG msg = {};

	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
};
