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
		root->childLeft = nullptr;
		root->childRight = nullptr;
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
		temp->childLeft = nullptr;
		temp->childRight = nullptr;
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

int CRedBlackTree::searchTree(int value, Node* temp)
{
	if (temp->value == value)
		return value;
	else if (temp->value > value && temp->childLeft != nullptr)
		searchTree(value, temp->childLeft);
	else if (temp->value < value && temp->childRight != nullptr)
		searchTree(value, temp->childRight);
	else return -1;
}

void CRedBlackTree::checkRBT(Node* temp)
{
	Node* uncle = nullptr;
	Node* tParent = nullptr;
	Node* gParent = nullptr;

	while (temp != root && getColour(temp) == Colour::Red && getColour(temp->parent) == Colour::Red)
	{
		uncle = getUncle(temp);
		tParent = temp->parent;
		gParent = tParent->parent;
		if (tParent == gParent->childLeft)
		{
			if (getColour(uncle) == Colour::Red)
			{
				setColour(uncle, Colour::Black);
				setColour(tParent, Colour::Black);
				setColour(gParent, Colour::Red);
				setColour(root, Colour::Black);
				temp = gParent;
			}
			else
			{
				if (temp == tParent->childRight)
				{
					rotateLeft(tParent);
					temp = tParent;
					tParent = temp->parent;
				}
				rotateRight(gParent);
				switchColour(tParent);
				switchColour(gParent);
				temp = tParent;
			}
		}
		else
		{
			if (getColour(uncle) == Colour::Red)
			{
				setColour(uncle, Colour::Black);
				setColour(tParent, Colour::Black);
				setColour(gParent, Colour::Red);
				setColour(root, Colour::Black);
				temp = gParent;
			}
			else
			{
				if (temp == tParent->childLeft)
				{
					rotateRight(tParent);
					temp = tParent;
					tParent = temp->parent;
				}
				rotateLeft(gParent);
				switchColour(tParent);
				switchColour(gParent);
				temp = tParent;
			}
		}
	}


	/*Node *tParent = nullptr;
	Node *gParent = nullptr;
	while (temp != root && getColour(temp) == Colour::Red && getColour(temp->parent) == Colour::Red)
	{
		parent = temp->parent;
		grandparent = parent->parent;
		if (parent == grandparent->childLeft) {
			Node *uncle = getUncle(temp);
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
	setColour(root, Colour::Black);*/

}



void CRedBlackTree::rotateLeft(Node * temp)
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

	/*Node *right_child = ptr->childRight;
	ptr->childRight = right_child->childLeft;

	if (ptr->childRight != nullptr)
		ptr->childRight->parent = ptr;

	right_child->parent = ptr->parent;

	if (ptr->parent == nullptr)
		root = right_child;
	else if (ptr == ptr->parent->childRight)
		ptr->parent->childLeft = right_child;
	else
		ptr->parent->childRight = right_child;

	right_child->childLeft = ptr;
	ptr->parent = right_child;*/
}



void CRedBlackTree::rotateRight(Node * temp)
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

	//Node *left_child = ptr->childLeft;
	//ptr->childLeft = left_child->childRight;

	//if (ptr->childLeft != nullptr)
	//	ptr->childLeft->parent = ptr;

	//left_child->parent = ptr->parent;

	//if (ptr->parent == nullptr)
	//	root = left_child;
	//else if (ptr == ptr->parent->childLeft)
	//	ptr->parent->childLeft = left_child;
	//else
	//	ptr->parent->childRight = left_child;

	//left_child->childRight = ptr;
	//ptr->parent = left_child;
}



std::string CRedBlackTree::showColour(Node * temp)
{
	if (temp->colour == Colour::Black)
		return "B: ";
	else
		return "R: ";
}



CRedBlackTree::Node* CRedBlackTree::getUncle(Node* temp)
{
	if (temp->parent->parent->childLeft == temp->parent)
		return temp->parent->parent->childRight;
	else
		return temp->parent->parent->childLeft;
}



void CRedBlackTree::setColour(Node * temp, Colour colour)
{
	temp->colour = colour;
}



CRedBlackTree::Colour CRedBlackTree::getColour(Node * temp)
{
	if (temp == nullptr)
		return Colour::Black;
	return temp->colour;
}

void CRedBlackTree::switchColour(Node* temp)
{
	if (getColour(temp) == Colour::Red)
		setColour(temp, Colour::Black);
	else
		setColour(temp, Colour::Red);
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