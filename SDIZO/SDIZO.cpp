// SDIZO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	//CInterface::Finterface();

	CRedBlackTree lol;
	lol.add(18);
	lol.add(10);
	lol.add(2);
	lol.add(13);
	lol.add(3);
	lol.add(5);
	lol.add(29);
	lol.add(9);
	lol.add(30);
	lol.add(6);
	lol.add(19);
	lol.add(28);
	lol.add(26);
	lol.add(25);
	lol.add(21);
	lol.add(7);

	lol.printTree();

	std::cout << "\n\n\n" << lol.search(3);

	system("PAUSE");
	return 0;
}
