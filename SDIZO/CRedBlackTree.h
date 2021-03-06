#pragma once


class CRedBlackTree
{
public:
	CRedBlackTree();
	~CRedBlackTree();
	void add(int value);
	void remove(int value);
	int search(int value);
	void printTree();
	
private:
	
	enum class Colour 
	{
		Red,
		Black
	};

	struct Node
	{
		Node* parent, *childLeft, *childRight;
		int value;
		Colour colour;

		Node(int value)
		{
			parent = nullptr;
			childLeft = nullptr;
			childRight = nullptr;
			this->value = value;
			colour = Colour::Red;
		}
	};
	Node *root;
	Node sentinel;

	void checkRBT(Node* temp);
	void rotateLeft(Node * temp);
	void rotateRight(Node * temp);

	void deleteTree(Node* temp);
	int searchTree(int value, Node* temp);
	
	Node* searchNode(int value, Node* temp);
	Node* getUncle(Node* temp);
	Node* getSuccessor(Node* temp);
	Node* minNode(Node* temp);

	void setColour(Node * temp, Colour colour);
	void switchColour(Node* temp);
	Colour getColour(Node * temp);
	
	void printTree(std::string sp, std::string sn, Node* p); // source: http://eduinf.waw.pl/inf/alg/001_search/0113.php
	std::string showColour(Node * temp);

};






	
	

