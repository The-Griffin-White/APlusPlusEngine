// DXApp
// Andre Berthiaume, June 2016
// Note: DX 11 SDK https://www.microsoft.com/en-us/download/details.aspx?id=6812
// Note on weird stuff with swap chain (1s and 2s) https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

#ifndef _DXApp
#define _DXApp

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include <string>

class Engine;

class DXApp : public Align16
{
private:	
	static float DelayPerFrame;	// 1/60, so 60fps...
	static float TotalTime;		// Used for monitoring the time since the beginning of the game

	// Main window handle
	HWND      mhMainWnd;

	Vect BackgroundColor;

	// Engine pointer to make the game work...
	Engine* pEngine;

	// DX application elements
	ID3D11Device* md3dDevice;					// Connects to the graphics card
	ID3D11DeviceContext* md3dImmediateContext;	// Settings for the GPU to use
	IDXGISwapChain* mSwapChain;					// image buffers used for rendering
	ID3D11RenderTargetView* mRenderTargetView;	// Where to send rendring operations (typically: points to one of the swap buffers)
	ID3D11DepthStencilView* mpDepthStencilView; // Needed to force depth-buffer operations

	GameTimer mTimer;
	std::wstring mMainWndCaption;
	int mClientWidth;
	int mClientHeight;

	void InitDirect3D();
	void InitDemo();
	void UpdateScene();
	void DrawScene();
	void CalculateFrameStats();

	// Shader loading utility. SHould be moved elsewhere later...
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// Debug utility
	void ReportLiveDXObjects();

	// Demo specific additions

	// Blend state
	ID3D11BlendState* TransparentBS;
	ID3D11RasterizerState* FrontFaceAsCCWRS;
	ID3D11RasterizerState* FrontFaceAsCCWRSWireframe;
	
public:
	DXApp(HWND hwnd, Engine* p);
	virtual ~DXApp();
	
	void FrameTick();
	const float GetTimeInSeconds() const;

	// overrides for handling mouse input.
	void OnMouseDown(WPARAM btnState, int xval, int yval);
	void OnMouseUp(WPARAM btnState, int xval, int yval);
	void OnMouseMove(WPARAM btnState, int xval, int yval);
	void OnMouseWheel(short delta);

	void SetSolidRender();
	void SetWireRender();
	void SetClearColor(const Vect& color);
	ID3D11DeviceContext* getContext();
	ID3D11RenderTargetView* getRenderTargetView();
	IDXGISwapChain* getSwapChain();
};

#endif _DXApp