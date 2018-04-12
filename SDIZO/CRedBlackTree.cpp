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



void CRedBlackTree::checkRBT(Node* &ptr)
{
	/*bool koniec = false;
	if (getColour(temp->parent) == Colour::Black)
		return;
	else
	{
		Node* gParent, *uncle;
		do {

			uncle = getUncle(temp);
			gParent = temp->parent->parent;
			if (temp->parent == temp->parent->parent->childLeft)
			{

				if (getColour(uncle) == Colour::Red)
				{
					setColour(temp->parent, Colour::Black);
					setColour(uncle, Colour::Black);
					if (gParent != root)
					{
						koniec = true;
						setColour(gParent, Colour::Red);
					}
					else
						temp = gParent;
				}

				if (getColour(uncle) == Colour::Black && temp->parent->childRight == temp && !koniec)
				{
					temp = temp->parent;
					rotateLeft(temp->parent);
				}

				setColour(gParent, Colour::Red);
				setColour(temp->parent, Colour::Black);
				rotateRight(gParent);
				koniec = true;
			}
			else
			{
				if (getColour(uncle) == Colour::Red)
				{
					setColour(temp->parent, Colour::Black);
					setColour(uncle, Colour::Black);
					if (gParent != root)
					{
						koniec = true;
						setColour(gParent, Colour::Red);
					}
					else
						temp = gParent;
				}

				if (getColour(uncle) == Colour::Black && temp->parent->childLeft == temp && !koniec)
				{
					rotateRight(temp->parent);
					temp = temp->parent;
				}


				setColour(gParent, Colour::Red);
				setColour(temp->parent, Colour::Black);
				rotateLeft(gParent);
				koniec = true;
			}
		} while (gParent != root && !koniec);
		setColour(root, Colour::Black);
	}*/
	Node *parent = nullptr;
	Node *grandparent = nullptr;
	while (ptr != root && getColour(ptr) == Colour::Red && getColour(ptr->parent) == Colour::Red) {
		std::cout << "lol2";
		parent = ptr->parent;
		grandparent = parent->parent;
		if (parent == grandparent->childLeft) {
			Node *uncle = grandparent->childRight;
			if (getColour(uncle) == Colour::Red) {
				setColour(uncle, Colour::Black);
				setColour(parent, Colour::Black);
				setColour(grandparent, Colour::Red);
				ptr = grandparent;
			}
			else {
				if (ptr == parent->childRight) {
					rotateLeft(parent);
					ptr = parent;
					parent = ptr->parent;
				}
				rotateRight(grandparent);
				std::swap(parent->colour, grandparent->colour);
				ptr = parent;
			}
		}
		else {
			Node *uncle = grandparent->childLeft;
			if (getColour(uncle) == Colour::Red) {
				setColour(uncle, Colour::Black);
				setColour(parent, Colour::Black);
				setColour(grandparent, Colour::Red);
				ptr = grandparent;
			}
			else {
				if (ptr == parent->childLeft) {
					rotateRight(parent);
					ptr = parent;
					parent = ptr->parent;
				}
				rotateLeft(grandparent);
				std::swap(parent->colour, grandparent->colour);
				ptr = parent;
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
		rChild->parent = temp->parent;
		temp->parent = rChild;
		if (tParent != nullptr)
		{
			if (temp == temp->parent->childLeft)
				temp->parent->childLeft = rChild;
			tParent->childRight = rChild;
		}
		else
			root = rChild;
	}
}



void CRedBlackTree::rotateRight(Node * &temp)
{
	/*Node *left_child = temp->childLeft;
	temp->childLeft = left_child->childRight;

	if (temp->childLeft != nullptr)
		temp->childLeft->parent = temp;

	left_child->parent = temp->parent;

	if (temp->parent == nullptr)
		root = left_child;
	else if (temp == temp->parent->childLeft)
		temp->parent->childLeft = left_child;
	else
		temp->parent->childRight = left_child;

	left_child->childRight = temp;
	temp->parent = left_child;*/
	/*Node* lChild = temp->childLeft;
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
			tParent->childRight = lChild;
		}
		else
			root = lChild;
	}*/
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