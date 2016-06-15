// MusicGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MusicGeneratorApp.h"




MusicGeneratorApp musicGeneratorApp;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	return musicGeneratorApp.winMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}
