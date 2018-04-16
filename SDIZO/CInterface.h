#pragma once
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include "CMeasure.h"

class CInterface
{
public:
	CInterface();
	~CInterface();
	
protected:
	void gotoxy(int x, int y);
	int probeInt(int input);
	void printArray();
	void readData(CFileStream &file);
	void writeData(CFileStream &file);
	void randomData();
	void startMenu();

	void menuArray();
	void menuList();
	void menuHeap();
	void menuRBT();
	void menuAVL();
	

	int menu_gl();
	void menu_gl_rysowanie(int x, int h);
	void menu_gl_podswietlenie(int x, int h, int wybor);
	int mainAlgorithm();
	void structureMenu();
	void structureArrayListMenu();
	void algorithmMenu();
	void algorithmMenu(int x, int h);
	void algorithmMenuHighlight(int x, int h, int wybor);

	int *array;
	long long int arrayTime[10] = { 0 };
	int size;
	const int TEST_SIZE = 1000; // size of structures during time measure 
	const int MAX_VALUE = 1000; // highest possible value to random draw;
	CMeasure testTime;
};