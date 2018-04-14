#pragma once
#include "CRedBlackTree.h"
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

		Node(int value)
		{
			parent = nullptr;
			childLeft = nullptr;
			childRight = nullptr;
			bf = 0;
			this->value = value;
		}
	};

	Node *root;

	void balanceTree(Node* temp);
	void rotateLeft(Node * temp);
	void rotateRight(Node * temp);
	void rotateDoubleLeft(Node * temp);
	void rotateDoubleRight(Node * temp);

	void removeNode(Node* temp);
	void deleteTree(Node* temp);
	int searchTree(int value, Node* temp);

	Node* searchNode(int value, Node* temp);
	Node* getUncle(Node* temp);
	Node* getSuccessor(Node* temp);
	Node* minNode(Node* temp);
	int height(Node* temp);

	void printTree(std::string sp, std::string sn, Node* p); // source: http://eduinf.waw.pl/inf/alg/001_search/0113.php
};

