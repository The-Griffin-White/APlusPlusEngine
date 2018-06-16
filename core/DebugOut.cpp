#include "DebugOut.h"

#include <Windows.h>
#include <stdio.h>
#include <stdarg.h>

char DebugMsg::DebugBuff[256] = { "no" };

void DebugMsg::out(char* A, ...)
{
	va_list args;
	va_start(args, A);
	vsprintf_s(DebugBuff, A, args);
	// convert the char* to a wchar_t*
	size_t newsize = strlen(DebugBuff) + 1;
	wchar_t * newText = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, newText, newsize, DebugBuff, _TRUNCATE);
	OutputDebugString(newText);
	delete[] newText;
};