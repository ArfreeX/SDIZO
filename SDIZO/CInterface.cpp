#include "stdafx.h"



CInterface::CInterface()
{
}


CInterface::~CInterface()
{
}

void CInterface::gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void CInterface::menu_gl_rysowanie(int x, int h)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
	gotoxy(10 + x, 0 + h);
	std::cout << "Operacje na tablicy";
	gotoxy(10 + x, 1 + h);
	std::cout << "Rysowanie kreski";
	gotoxy(10 + x, 2 + h);
	std::cout << "Sprawdzanie wcisnietego klawisza";
	gotoxy(10 + x, 3 + h);
	std::cout << "Klasyfikacja wzrostu";
	gotoxy(10 + x, 4 + h);
	std::cout << "Rysowanie choinki";
	gotoxy(10 + x, 5 + h);
	std::cout << "Liczenie min/max";
	gotoxy(10 + x, 6 + h);
	std::cout << "Koniec programu";
}
void CInterface::menu_gl_podswietlenie(int x, int h, int wybor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
	gotoxy(10 + x, wybor + h);
	switch (wybor)
	{
	case 0:std::cout << "Operacje na tablicy";
		break;
	case 1:std::cout << "Rysowanie kreski";
		break;
	case 2:std::cout << "Sprawdzanie wcisnietego klawisza";
		break;
	case 3:std::cout << "Klasyfikacja wzrostu";
		break;
	case 4:std::cout << "Rysowanie choinki";
		break;
	case 5:std::cout << "Liczenie min/max";
		break;
	case 6:std::cout << "Koniec programu";
		break;
	}
}

int CInterface::menu_gl()
{
	int wybor;
	int poprzedniWybor;
	bool wykonujPetle;
	while (1)
	{
		int h = 5;
		int x = 25;
		wybor = 0;
		poprzedniWybor = wybor;
		wykonujPetle = true;
		system("cls");
		gotoxy(10 + x, 0 + (h - 4));
		std::cout << "+++++++++++++++++++++";
		gotoxy(10 + x, 0 + (h - 3));
		std::cout << "+++++MENU+GLOWNE+++++";
		gotoxy(10 + x, 0 + (h - 2));
		std::cout << "+++++++++++++++++++++";
		system("COLOR 1B");
		menu_gl_rysowanie(x, h);
		//23 && 31
		while (wykonujPetle)
		{
			menu_gl_podswietlenie(x, h, wybor);
			poprzedniWybor = wybor;
			switch (_getch())
			{
			case 224:
				switch (_getch())
				{
				case 72:
					if (0 < wybor) wybor--;
					else wybor = 6;
					break;
				case 80:
					if (wybor < 6) wybor++;
					else wybor = 0;

					break;

				case 77:
					system("cls");
					return wybor;
				}
				break;
			case 13:
				system("cls");
				return wybor;
			}
			menu_gl_rysowanie(x, h);
		}
	}
	system("cls");
	return 100;
}

void CInterface::Finterface()
{
	bool program = true;
	do
	{
		switch (menu_gl())
		{
		case 0://menu_tablica();
			break;
		case 1://kreska();
			break;
		case 2://klawisz();
			break;
		case 3://wzrost();
			break;
		case 4://choinka();
			break;
		case 5://min_max();
			break;
		case 6:
			program = false;
			break;
		default: system("cls");
			break;
		}
	} while (program);
	system("cls");
	std::cout << "\nKoniec programu.\n";
}