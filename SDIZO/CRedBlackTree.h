#pragma once


class CRedBlackTree
{
public:
	CRedBlackTree();
	~CRedBlackTree();
	void add(int value);
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

	void checkRBT(Node* &temp);
	void rotateLeft(Node * &temp);
	void rotateRight(Node * &temp);

	Node* getUncle(Node* &temp);
	void setColour(Node * &temp, Colour colour);
	Colour getColour(Node * &temp);
	
	void printTree(std::string sp, std::string sn, Node* p); // source: http://eduinf.waw.pl/inf/alg/001_search/0113.php
	std::string showColour(Node * &temp);

};






	
	

