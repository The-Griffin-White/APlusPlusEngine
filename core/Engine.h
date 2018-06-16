#ifndef ENGINE_H
#define ENGINE_H

#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include <WindowsX.h>
#include "../DX Application/Resource.h"
#include "DXApp.h"
#include <assert.h>

class DemoScene;

#define ENGINE_WINDOW_NAME_LENGTH 128

class Engine : public Align16
{
protected:
	Engine();
	virtual ~Engine();

	virtual void Initialize() = 0;
	virtual void UnLoadContent() = 0;
	virtual void LoadContent() = 0;

	// ad hoc stuff to make the demo work...
	ID3D11Device* md3dDevice;					// Connects to the graphics card
	ID3D11DeviceContext* md3dImmediateContext;	// Settings for the GPU to use
	int mClientWidth;
	int mClientHeight;

	int privRun(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow);

	void setWindowName(const char* windowName);
	void setWidthHeight(const int width, const int height);
	void SetClearColor(const Vect col, float a);
	void SetClearColor(const float r, const float g, const float b, const float a);

	static void SetSolidRender();
	static void SetWireRender();

	int getWidth();
	int getHeight();
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;

	const float GetTimeInSeconds() const;

	static LRESULT CALLBACK    ourWndProc(HWND, UINT, WPARAM, LPARAM);
	
	void TakeDemoInformation(
		ID3D11Device* Device, ID3D11DeviceContext* Context,
		int Width, int Height
	);

private:
	HRESULT InitWindow
	(
		HINSTANCE hInstance, int nCmdShow, 
		const wchar_t* windowName = L"Main Window", 
		const int width = 800, const int height = 600
	);
	void InitApp();
	void CleanupApp();

	static HINSTANCE               g_hInst;
	static HWND                    g_hWnd;
	static DXApp*				   g_dxapp;
	static ID3D11Device*           currDevice;

	friend class EngineAttorneyToGraphics;
	static ID3D11Device* getDevice();
	static ID3D11DeviceContext* getContext();

	const wchar_t* name;
	static int w;
	static int h;
};




#endif /* ENGINE_H */
