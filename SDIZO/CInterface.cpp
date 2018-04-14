#include "stdafx.h"

CInterface::CInterface() 
{
	startMenu();
}
CInterface::~CInterface()
{
	delete[] array;
}

void CInterface::gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void CInterface::structureMenu()
{
	system("cls");
	std::cout << "Structure menu\n";
	std::cout << "[1] Fill up with data\n";
	std::cout << "[2] Print structure\n";
	std::cout << "[3] Add element\n";
	std::cout << "[4] Remove element\n";
	std::cout << "[5] Search value\n";
	std::cout << "[6] Exit\n";
}

void CInterface::structureArrayListMenu()
{
	system("cls");
	std::cout << "Structure menu\n";
	std::cout << "[1] Fill up with data\n";
	std::cout << "[2] Print structure\n";
	std::cout << "[3] Add element: front\n";
	std::cout << "[4] Add element: on index\n";
	std::cout << "[5] Add element: back\n";
	std::cout << "[6] Remove element: front\n";
	std::cout << "[7] Remove element: on index\n";
	std::cout << "[8] Remove element: back\n";
	std::cout << "[9] Search value\n";
	std::cout << "[10] Exit\n";
}

void CInterface::menuArray()
{
	CDynamicArray testArray;
	int input;
	do {
		structureArrayListMenu();
		std::cin >> input;
		if (!std::cin) {
			std::cout << "\nBad value!\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cin >> input;
		}
		switch (input)
		{
		case 1: 
			if (size > 0)
				for (int i = 0; i < size; i++)
					testArray.addEnd(array[i]);
			break;
		case 2: 
			system("cls");
			long long int x;
			testTime.start();
			testArray.printArray();
		    x = testTime.elapsed();
			std::cout << x;
			system("pause");
			break;
		case 3: //arrayAddF();
			break;
		case 4: //arrayAddI();
			break;
		case 5: //arrayAddB();
			break;
		case 6: //arrayRemoveF();
			break;
		case 7: //arrayRemoveI();
			break;
		case 8: //arrayRemoveB();
			break;
		case 9: //arraySearch();
			break;
		}
	} while (input != 10);
	
}


void CInterface::menuList()
{
	int input;
	do {
		structureArrayListMenu();
		std::cin >> input;
		if (!std::cin) {
			std::cout << "\nBad value!\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cin >> input;
		}
	} while (input != 10);
}

void CInterface::menuHeap()
{
	int input;
	do {
		structureMenu();
		std::cin >> input;
		if (!std::cin) {
			std::cout << "\nBad value!\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cin >> input;
		}
	} while (input != 5);
}

void CInterface::menuRBT()
{
	int input;
	do {
		structureMenu();
		std::cin >> input;
		if (!std::cin) {
			std::cout << "\nBad value!\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cin >> input;
		}
	} while (input != 5);
}

void CInterface::menuAVL()
{
	int input;
	do {
		structureMenu();
		std::cin >> input;
		if (!std::cin) {
			std::cout << "\nBad value!\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cin >> input;
		}
	} while (input != 5);
}

void CInterface::readData(CFileStream &file)
{
	system("cls");
	std::cout << "Insert file path\n";
	file.openFile();
	array = file.readData(array, size);
	std::cout << "\nData readed\n";
	system("Pause");
}

void CInterface::writeData(CFileStream &file)
{
	file.write(array, size);
}

void CInterface::randomData()
{
	CNumberGen gen(MAX_VALUE);
	system("cls");
	std::cout << "Insert size of data [ -1 for random size ]\n";
	int input;
	std::cin >> input;
	if (!std::cin) {
		std::cout << "\nBad value!\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cin >> input;
	}
	if (input >= 0)
	{
		size = input;
	}
	else
		size = TEST_SIZE;
	array = new int[size];
	for (int i = 0; i < size; i++)
		array[i] = gen.randomNumber();

}

void CInterface::printArray()
{
	system("cls");
	for (int i = 0; i < size; i++)
		std::cout << array[i] << " ";
	std::cout << "\nSize: " << size << std::endl;
	system("pause");
}


void CInterface::algorithmMenu()
{
	bool program = true;
	do
	{
		switch (mainAlgorithm())
		{
		case 0:	menuArray();
			break;
		case 1: menuList();
			break;
		case 2: menuHeap();
			break;
		case 3: menuRBT();
			break;
		case 4: menuAVL();
			break;
		case 5:
			program = false;
			break;
		default: system("cls");
			break;
		}
	} while (program);
	system("cls");
}

void CInterface::startMenu()
{
	CFileStream file;
	bool program = true;
	do
	{
		switch (menu_gl())
		{
		case 0:	readData(file);
			break;
		case 1: writeData(file);
			break;
		case 2: randomData();
			break;
		case 3: algorithmMenu();
			break;
		case 4: printArray();
			break;
		case 5:
			program = false;
			break;
		default: system("cls");
			break;
		}
	} while (program);
	system("cls");
	std::cout << "\nKoniec programu.\n";
}


//============================================================================//
//						Implementation of txt menu							  //
//============================================================================//

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
		gotoxy(10 + x, 0 + (h - 4));
		std::cout << "//=====================//";
		gotoxy(10 + x, 0 + (h - 3));
		std::cout << "//      MAIN MENU      //";
		gotoxy(10 + x, 0 + (h - 2));
		std::cout << "//=====================//";
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
					else wybor = 5;
					break;
				case 80:
					if (wybor < 5) wybor++;
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

void CInterface::menu_gl_rysowanie(int x, int h)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
	gotoxy(10 + x, 0 + h);
	std::cout << "Read data";
	gotoxy(10 + x, 1 + h);
	std::cout << "Save results";
	gotoxy(10 + x, 2 + h);
	std::cout << "Random data";
	gotoxy(10 + x, 3 + h);
	std::cout << "Algorithms";
	gotoxy(10 + x, 4 + h);
	std::cout << "Print data";
	gotoxy(10 + x, 5 + h);
	std::cout << "End";
}

void CInterface::menu_gl_podswietlenie(int x, int h, int wybor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
	gotoxy(10 + x, wybor + h);
	switch (wybor)
	{
	case 0:std::cout << "Read data";
		break;
	case 1:std::cout << "Save results";
		break;
	case 2:std::cout << "Random data";
		break;
	case 3:std::cout << "Algorithms";
		break;
	case 4:std::cout << "Print data";
		break;
	case 5:std::cout << "End";
		break;
	}
}

int CInterface::mainAlgorithm()
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
		std::cout << "//=====================//";
		gotoxy(10 + x, 0 + (h - 3));
		std::cout << "//      ALGORITHMS     //";
		gotoxy(10 + x, 0 + (h - 2));
		std::cout << "//=====================//";
		system("COLOR 1B");
		algorithmMenu(x, h);
		//23 && 31
		while (wykonujPetle)
		{
			algorithmMenuHighlight(x, h, wybor);
			poprzedniWybor = wybor;
			switch (_getch())
			{
			case 224:
				switch (_getch())
				{
				case 72:
					if (0 < wybor) wybor--;
					else wybor = 5;
					break;
				case 80:
					if (wybor < 5) wybor++;
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
			algorithmMenu(x, h);
		}
	}
	system("cls");
	return 100;
}

void CInterface::algorithmMenu(int x, int h)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
	gotoxy(10 + x, 0 + h);
	std::cout << "Array";
	gotoxy(10 + x, 1 + h);
	std::cout << "List";
	gotoxy(10 + x, 2 + h);
	std::cout << "Heap";
	gotoxy(10 + x, 3 + h);
	std::cout << "RBT";
	gotoxy(10 + x, 4 + h);
	std::cout << "AVL";
	gotoxy(10 + x, 5 + h);
	std::cout << "Return";
}

void CInterface::algorithmMenuHighlight(int x, int h, int wybor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
	gotoxy(10 + x, wybor + h);
	switch (wybor)
	{
	case 0:std::cout << "Array";
		break;
	case 1:std::cout << "List";
		break;
	case 2:std::cout << "Heap";
		break;
	case 3:std::cout << "RBT";
		break;
	case 4:std::cout << "AVL";
		break;
	case 5:std::cout << "Return";
		break;
	}
}
