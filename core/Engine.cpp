#include "Engine.h"

HINSTANCE Engine::g_hInst = nullptr;
HWND Engine::g_hWnd = nullptr;
DXApp* Engine::g_dxapp = nullptr;
ID3D11Device* Engine::currDevice = nullptr;

int Engine::w = 800;
int Engine::h = 600;

Engine::Engine()
{
	name = L"APPEcore Demo";
}

Engine::~Engine()
{
	delete g_dxapp;
}

const float Engine::GetTimeInSeconds() const
{
	return g_dxapp->GetTimeInSeconds();
}

void Engine::setWindowName(const char* windowName)
{
	// convert the char* to a wchar_t*
	size_t newsize = strlen(windowName) + 1;
	wchar_t * newName = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, newName, newsize, windowName, _TRUNCATE);
	SetWindowText(g_hWnd, newName);
	delete[] newName;
}
void Engine::setWidthHeight(const int width, const int height)
{
	w = width;
	h = height;
	SetWindowPos(g_hWnd, HWND_TOPMOST, 0, 0, w, h, SWP_NOMOVE);
}
void Engine::SetClearColor(const Vect col, const float a)
{
	// this is handled in dxapp...
	Vect newCol;
	newCol.set(col.X(), col.Y(), col.Z(), a);
	g_dxapp->SetClearColor(newCol);
}
void Engine::SetClearColor(const float r, const float g, const float b, const float a)
{
	// this is handled in dxapp...
	Vect newColor;
	newColor.set(r, g, b, a);
	g_dxapp->SetClearColor(newColor);
}

int Engine::getWidth()
{
	return w;
}

int Engine::getHeight()
{
	return h;
}

void Engine::TakeDemoInformation(
	ID3D11Device* Device, ID3D11DeviceContext* Context,
	int Width, int Height
)
{
	md3dDevice = Device;
	currDevice = Device;
	md3dImmediateContext = Context;
	mClientWidth = Width;
	mClientHeight = Height;
}

ID3D11Device* Engine::getDevice()
{
	return currDevice;
}

ID3D11DeviceContext* Engine::getContext()
{
	return g_dxapp->getContext();
}

void Engine::SetSolidRender()
{
	g_dxapp->SetSolidRender();
}
void Engine::SetWireRender()
{
	g_dxapp->SetWireRender();
}

LRESULT CALLBACK    WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return Engine::ourWndProc(hWnd, message, wParam, lParam);
}

int Engine::privRun(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Window initialization
	HRESULT hr = InitWindow(hInstance, nCmdShow, name);
	assert(SUCCEEDED(hr));  // We'll be doing a lot of this...

	// Initialize the application that will make use of this window.
	// In this case, it's our APPEcore Game or Demo
	InitApp();

	// Main message loop and application calls
	// This is how MS/Windows deal with various input/widgets/UI/Menu stuff
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		g_dxapp->FrameTick();
	}

	// Shutting down the app
	CleanupApp();

	return (int)msg.wParam;
}

//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT Engine::InitWindow
(
	HINSTANCE hInstance, int nCmdShow,
	const wchar_t* windowName,
	const int width, const int height
)
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"MainlWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// Create window
	g_hInst = hInstance;
	RECT rc = { 0, 0, width, height }; // Initial window dimentions. 

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	g_hWnd = CreateWindow(L"MainlWindowClass", windowName,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);
	if (!g_hWnd)
		return E_FAIL;

	// Note: We won't bother dealing with resizing/fullscreen, etc

	ShowWindow(g_hWnd, nCmdShow);

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK Engine::ourWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
		// Early exit using ESC key: very useful during development
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
			return 0;
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		SetCapture(g_hWnd);
		g_dxapp->OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;

	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		ReleaseCapture();
		g_dxapp->OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;

	case WM_MOUSEMOVE:
		g_dxapp->OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
void Engine::InitApp()
{
	g_dxapp = new DXApp(g_hWnd, this);

	this->Initialize();
	this->LoadContent();
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void Engine::CleanupApp()
{
	this->UnLoadContent();
//	delete g_dxapp;
}