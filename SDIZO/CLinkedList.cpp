#include "stdafx.h"



CLinkedList::CLinkedList()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

void CLinkedList::addOnStart(int value)
{
	if (!checkEmpty(value))
	{
		Node* temp = head;
		head = new Node(value);
		temp->previous = head;
		head->next = temp;
		size++;
	}
}

void CLinkedList::addOnIndex(int value, int position)
{
	if (position < 0 || position > size)
	{
		std::cout << "Invalid index";
		return;
	}
	else if (position == 0)
		addOnStart(value);
	else if (position == size)
		addOnEnd(value);
	else if (position > (size / 2))
	{
		Node* temp = tail;
		Node* newNode = new Node(value);
		for (int i = size; i > position + 1; i--)
			temp = temp->previous;

		newNode->previous = temp->previous;
		newNode->previous->next = newNode;
		temp->previous = newNode;
		newNode->next = temp;
		size++;
	}
	else
	{
		Node* temp = head;
		Node* newNode = new Node(value);
		for (int i = 0; i < position - 1; i++)
			temp = temp->next;

		temp->next->previous = newNode;
		newNode->next = temp->next;
		temp->next = newNode;
		newNode->previous = temp;
		size++;
	}
}

void CLinkedList::addOnEnd(int value)
{

	if (!checkEmpty(value))
	{
		Node* temp = tail;
		tail = new Node(value);
		temp->next = tail;
		tail->previous = temp;
		size++;
	}
}

int CLinkedList::searchIndex(int position)
{
	if (position < size && position >= size / 2)
	{
		Node* temp = tail;
		for (int i = size - 1; i > position; i--)
			temp = temp->previous;
		return temp->value;
	}
	else if (position < size / 2 && position >= 0)
	{
		Node* temp = head;
		for (int i = 0; i < position; i++)
			temp = temp->next;
		return temp->value;
	}
	else
		std::cout << "Invalid index";
	return 0;

}
int CLinkedList::searchValue(int value)
{
	Node* temp = head;
	int i = 0;
	while (temp != nullptr)
	{
		if (temp->value == value)
			return i;
		temp = temp->next;
		i++;
	}
	return -1;
}
void CLinkedList::removeStart()
{
	Node *temp = head->next;
	delete head;
	head = temp;
	head->previous = nullptr;
	size--;
}

void CLinkedList::removeOnIndex(int position)
{
	if (position >= size)
	{
		std::cout << "Invalid position";
		return;
	}
	else if (position == 0)
		removeStart();
	else if (position == size - 1)
		removeEnd();
	else if (position >= (size / 2))
	{
		Node* temp = tail;
		Node* buf;

		for (int i = size - 1; i > position + 1; i--)
			temp = temp->previous;

		buf = temp->previous->previous;
		delete temp->previous;
		buf->next = temp;
		temp->previous = buf;

		size--;
	}
	else
	{
		Node* temp = head;
		Node* buf;

		for (int i = 0; i < position - 1; i++)
			temp = temp->next;

		buf = temp->next->next;
		delete temp->next;
		temp->next = buf;
		buf->previous = temp;

		size--;
	}
}
void CLinkedList::removeEnd()
{
	Node *temp = tail->previous;
	delete tail;
	tail = temp;
	tail->next = nullptr;
	size--;
}

void CLinkedList::print()
{
	if (head != nullptr)
	{
		Node* temp = head;
		int i = 0;
		while (temp->next != nullptr)
		{
			std::cout << i << ". " << temp->value << std::endl;
			temp = temp->next;
			i++;
		}
		std::cout << i << ". " << temp->value << std::endl;
		std::cout << "\nSize: " << size << std::endl;
	}
	else
		std::cout << "List is empty";
}

void CLinkedList::printReverse()
{
	if (tail != nullptr)
	{
		Node* temp = tail;
		int i = 0;
		while (temp->previous != nullptr)
		{
			std::cout << i << ". " << temp->value << std::endl;
			temp = temp->previous;
			i++;
		}
		std::cout << i << ". " << temp->value << std::endl;
		std::cout << "\nSize: " << size << std::endl;
	}
	else
		std::cout << "List is empty";
}

bool CLinkedList::checkEmpty(int value)
{
	if (head == nullptr || tail == nullptr)
	{
		head = new Node(value);
		tail = head;
		size++;
		return true;
	}
	return false;
}

