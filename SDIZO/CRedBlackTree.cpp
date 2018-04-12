#include "stdafx.h"
#include "CRedBlackTree.h"


CRedBlackTree::CRedBlackTree()
{
	root = nullptr;
}


CRedBlackTree::~CRedBlackTree()
{
	delete root;
}



void CRedBlackTree::add(int value)
{
	if (root == nullptr)
	{
		root = new Node(value);
		setColour(root, Colour::Black);
		root->parent = nullptr;
		//root->parent = root;
		return;
	}
	else
	{
		Node* temp = root;
		Node* buff = temp;
		while (temp != nullptr)
		{
			buff = temp;
			if (temp->value > value)
				temp = temp->childLeft;
			else
				temp = temp->childRight;
		}

		temp = new Node(value);
		if (value < buff->value)
			buff->childLeft = temp;
		else
			buff->childRight = temp;
		temp->parent = buff;
		checkRBT(temp);
	}

}

int CRedBlackTree::search(int value)
{
	if (root != nullptr)
		searchTree(value, root);
	else
		return -1;
}

int CRedBlackTree::searchTree(int value, Node* &temp)
{
	if (temp->value == value)
		return value;
	else if (temp->value > value && temp->childLeft != nullptr)
		searchTree(value, temp->childLeft);
	else if (temp->value < value && temp->childRight != nullptr)
		searchTree(value, temp->childRight);
	else return -1;
}

void CRedBlackTree::checkRBT(Node* &temp)
{
	/*Node* uncle = nullptr;
	Node* tParent = nullptr;
	while (true)
	{
		uncle = getUncle(temp);
		tParent = temp->parent;
		if (getColour(uncle) == Colour::Red)
		{
			setColour(uncle, Colour::Black);
			setColour(tParent, Colour::Black);
			setColour(tParent->parent, Colour::Red);
			setColour(root, Colour::Black);
			temp = tParent->parent;
			continue;
		}
		else
		{
			if (temp == tParent->childRight)
			{
				rotateLeft(tParent);
				temp = tParent;
				rotateRight(temp->parent);
				std::swap(temp->parent->colour, temp->colour);
				break;
			}
			else
			{
				rotateRight(tParent);
				temp = tParent;
				rotateLeft(temp->parent);
				std::swap(temp->parent->colour, temp->colour);
				break;
			}
		}
	}*/

	Node *parent = nullptr;
	Node *grandparent = nullptr;
	while (temp != root && getColour(temp) == Colour::Red && getColour(temp->parent) == Colour::Red) 
	{
		parent = temp->parent;
		grandparent = parent->parent;
		if (parent == grandparent->childLeft) {
			Node *uncle = grandparent->childRight;
			if (getColour(uncle) == Colour::Red) {
				setColour(uncle, Colour::Black);
				setColour(parent, Colour::Black);
				setColour(grandparent, Colour::Red);
				temp = grandparent;
			}
			else {
				if (temp == parent->childRight) {
					rotateLeft(parent);
					temp = parent;
					parent = temp->parent;
				}
				rotateRight(grandparent);
				std::swap(parent->colour, grandparent->colour);
				temp = parent;
			}
		}
		else {
			Node *uncle = grandparent->childLeft;
			if (getColour(uncle) == Colour::Red) {
				setColour(uncle, Colour::Black);
				setColour(parent, Colour::Black);
				setColour(grandparent, Colour::Red);
				temp = grandparent;
			}
			else {
				if (temp == parent->childLeft) {
					rotateRight(parent);
					temp = parent;
					parent = temp->parent;
				}
				rotateLeft(grandparent);
				std::swap(parent->colour, grandparent->colour);
				temp = parent;
			}
		}
	}
	setColour(root, Colour::Black);

}



void CRedBlackTree::rotateLeft(Node * &temp)
{
	Node* rChild = temp->childRight;
	if (rChild != nullptr)
	{
		Node* tParent = temp->parent;
		temp->childRight = rChild->childLeft;
		if (temp->childRight != nullptr)
			temp->childRight->parent = temp;
		rChild->childLeft = temp;
		rChild->parent = tParent;
		temp->parent = rChild;
		if (tParent != nullptr)
		{
			if (temp == tParent->childLeft)
				tParent->childLeft = rChild;
			else
				tParent->childRight = rChild;
		}
		else
			root = rChild;
	}
}



void CRedBlackTree::rotateRight(Node * &temp)
{
	Node* lChild = temp->childLeft;
	if (lChild != nullptr)
	{
		Node* tParent = temp->parent;
		temp->childLeft = lChild->childRight;
		if (temp->childLeft != nullptr)
			temp->childLeft->parent = temp;
		lChild->childRight = temp;
		lChild->parent = temp->parent;
		temp->parent = lChild;
		if (tParent != nullptr)
		{
			if (temp == temp->parent->childLeft)
				temp->parent->childLeft = lChild;
			else
				tParent->childRight = lChild;
		}
		else
			root = lChild;
	}
}



std::string CRedBlackTree::showColour(Node * &temp)
{
	if (temp->colour == Colour::Black)
		return "B: ";
	else
		return "R: ";
}
	


CRedBlackTree::Node* CRedBlackTree::getUncle(Node* &temp)
{
	if (temp->parent->childLeft == temp->parent)
		return temp->parent->childRight;
	else
		return temp->parent->childLeft;
}



void CRedBlackTree::setColour(Node * &temp, Colour colour)
{
	temp->colour = colour;
}



CRedBlackTree::Colour CRedBlackTree::getColour(Node * &temp)
{
	if (temp == nullptr)
		return Colour::Black;
	return temp->colour;
}



void CRedBlackTree::printTree()
{
	printTree("", "", root);
}



void CRedBlackTree::printTree(std::string sp, std::string sn, Node* p) // source: http://eduinf.waw.pl/inf/alg/001_search/0113.php
{
	std::string s, cr, cl, cp;
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;

	if (p != nullptr)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		printTree(s + cp, cr, p->childRight);

		s = s.substr(0, sp.length() - 2);
		std::cout << s << sn << showColour(p) << p->value << std::endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		printTree(s + cp, cl, p->childLeft);
	}
}