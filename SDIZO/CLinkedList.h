#pragma once
#include <iostream>

class CLinkedList
{
public:
	CLinkedList();

	void addOnStart(int value);
	void addOnIndex(int value, int position);
	void addOnEnd(int value);
		
	int searchIndex(int position);	
	int searchValue(int value);

	void removeStart();	
	void removeOnIndex(int position);
	void removeEnd();

	void print();
	void printReverse();
		

	private:

		struct Node
		{
			int value;
			Node *next;
			Node *previous;

			Node(int value)
			{
				this->value = value;
				next = nullptr;
				previous = nullptr;
			}
		};

		Node* head, *tail;
		int size;

		bool checkEmpty(int value);
};

