#pragma once
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <string>
class CInterface
{
public:
	static void Finterface();
	CInterface();
	~CInterface();
private:
	static void gotoxy(int x, int y);
	static void menu_gl_rysowanie(int x, int h);
	static void menu_gl_podswietlenie(int x, int h, int wybor);
	static int menu_gl();


};