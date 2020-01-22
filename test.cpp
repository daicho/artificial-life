#include <windows.h>
#include "d3d8.h"
#define TITLE 	TEXT("Kitty on your lap")

IDirect3D8 * pDirect3D;
IDirect3DDevice8 * pD3Device;

LRESULT CALLBACK WndProc(HWND hWnd , UINT msg , WPARAM wp , LPARAM lp) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd , msg , wp , lp);
}

int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance ,
			PSTR lpCmdLine , int nCmdShow) {
	MSG msg;
	HWND hWnd;
	WNDCLASS winc;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	pDirect3D = Direct3DCreate8(D3D_SDK_VERSION);
	pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT , &d3ddm);

	ZeroMemory(&d3dpp , sizeof (D3DPRESENT_PARAMETERS));
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;

	winc.style 		= CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc	= WndProc;
	winc.cbClsExtra		= winc.cbWndExtra = 0;
	winc.hInstance		= hInstance;
	winc.hIcon		= LoadIcon(NULL , IDI_APPLICATION);
	winc.hCursor		= LoadCursor(NULL , IDC_ARROW);
	winc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName	= NULL;
	winc.lpszClassName	= TEXT("KITTY");

	if (!RegisterClass(&winc)) return 0;

	hWnd = CreateWindow(
		TEXT("KITTY") , TITLE , WS_OVERLAPPEDWINDOW | WS_VISIBLE ,
		CW_USEDEFAULT , CW_USEDEFAULT , CW_USEDEFAULT , CW_USEDEFAULT ,
		NULL , NULL , hInstance , NULL
	);
	if (!hWnd) return 0;

	pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT , D3DDEVTYPE_HAL , hWnd ,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING , &d3dpp , &pD3Device
	);

	while (GetMessage(&msg , NULL , 0 , 0 )) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	pDirect3D->Release();
	pD3Device->Release();
	return msg.wParam;
}
