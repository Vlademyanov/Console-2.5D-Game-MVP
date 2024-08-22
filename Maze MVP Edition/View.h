#ifndef _VIEW_H
#define _VIEW_H
#pragma once
#include <windows.h>
#include <set>
#include <iostream>
#include <string>
#include <windows.h>

class View
{
public:

	View();
	void setFPS(float FPS);						// FPS
	float getFPS();

	std::set<char> getUserInput();

	void setWidth(int WIDTH);
	int getWidth();

	void setHeight(int HEIGHT);
	int getHeight();

	void initScreen();
	void setCharPixel(int y, int x, short charPixel);
	void updateConsole();

private:
	float FPS;
	int WIDTH;
	int HEIGHT;
	wchar_t* screen = new wchar_t[WIDTH * HEIGHT];
	HANDLE console;
	DWORD painted;

};

#endif // _VIEW_H