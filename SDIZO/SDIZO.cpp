// SDIZO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	CAVLTree tree;
	for (int i = 0; i < 100; i++)
		tree.add(i);
	tree.remove(79);
	tree.printTree();
	std::cout<<tree.search(5);
	std::cout << std::endl;
	system("PAUSE");
	return 0;
	
}
