//--------------------------------------------------------------------------------------
// File: MainWindow.cpp
//
// Heavily inspired by http://msdn.microsoft.com/en-us/library/windows/apps/ff729718.aspx
#include <WindowsX.h>
#include "resource.h"
#include "DXApp.h"
#include <assert.h>

#include "Engine/APlusPlusEngine.h"

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	APlusPlusEngine::RunGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	APlusPlusEngine::TerminateGame();

	return 0;
}