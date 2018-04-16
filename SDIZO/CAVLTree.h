#pragma once
#include <iostream>
#include <string>

class CAVLTree
{
public:
	CAVLTree();
	~CAVLTree();
	void add(int value);
	void remove(int value);
	int search(int value);
	void printTree();

private:

	struct Node
	{
		Node* parent, *childLeft, *childRight;
		int value, bf;

		Node(int value)  // konstruktor struktury
		{
			parent = nullptr;
			childLeft = nullptr;
			childRight = nullptr;
			bf = 0;     // wspolczynnik balansu drzewa
			this->value = value;
		}
	};

	Node *root;

	void balanceTree(Node* temp); // balansowanie drzewa po dodaniu elementu
	void rotateLeft(Node * temp);   // rozne rotacje 
	void rotateRight(Node * temp);
	void rotateDoubleLeft(Node * temp);
	void rotateDoubleRight(Node * temp);

	void removeNode(Node* temp);
	void deleteTree(Node* temp); // usuwanie drzewa -> destruktor
	int searchTree(int value, Node* temp);
	Node* searchNode(int value, Node* temp);

	Node* getUncle(Node* temp); // zwraca wujka od wezla
	Node* getSuccessor(Node* temp); // zwraca nastepnika wezla
	Node* minNode(Node* temp); 
	int height(Node* temp);

	void printTree(std::string sp, std::string sn, Node* p); // source: http://eduinf.waw.pl/inf/alg/001_search/0113.php
};

