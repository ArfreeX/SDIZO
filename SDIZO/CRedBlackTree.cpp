#include "stdafx.h"



CRedBlackTree::CRedBlackTree() : sentinel(0)
{
	root = nullptr;
	sentinel.colour = Colour::Black;
}


CRedBlackTree::~CRedBlackTree()
{
	deleteTree(root);
}

void CRedBlackTree::deleteTree(Node* temp)
{
	if (temp->childLeft != &sentinel)
		deleteTree(temp->childLeft);
	if (temp->childRight != &sentinel)
		deleteTree(temp->childRight);
	delete temp;
}

void CRedBlackTree::add(int value)
{
	if (root == nullptr)
	{
		root = new Node(value);
		setColour(root, Colour::Black);
		root->parent = nullptr;
		root->childLeft = &sentinel;
		root->childRight = &sentinel;
		return;
	}
	else
	{
		Node* temp = root;
		Node* buff = temp;
		while (temp != &sentinel)
		{
			buff = temp;
			if (temp->value > value)
				temp = temp->childLeft;
			else
				temp = temp->childRight;
		}

		temp = new Node(value);
		temp->childLeft = &sentinel;
		temp->childRight = &sentinel;
		if (value < buff->value)
			buff->childLeft = temp;
		else
			buff->childRight = temp;
		temp->parent = buff;
		checkRBT(temp);
	}

}

void CRedBlackTree::remove(int value)
{
	Node* temp = searchNode(value, root);

	if ( temp != &sentinel)
	{
		Node* buff, *son, *brother;

		if (temp->childLeft == &sentinel || temp->childRight == &sentinel)
			buff = temp;
		else
			buff = getSuccessor(temp);

		if (buff->childLeft == &sentinel)
			son = buff->childRight;
		else
			son = buff->childLeft;
		son->parent = buff->parent;

		if (buff->parent == nullptr)
		{
			root = son;
		}
		else if (buff == buff->parent->childLeft) // version3. updt
			buff->parent->childLeft = son;
		else
			buff->parent->childRight = son;
		if (buff != temp)
			temp->value = buff->value;
		if (getColour(buff) != Colour::Red)
		{
			while (son != root && getColour(son) == Colour::Black)
			{
				if (son != son->parent->childRight) 
				{
					brother = son->parent->childRight;
					if (getColour(brother) != Colour::Black)
					{
						setColour(brother, Colour::Black);
						setColour(son->parent, Colour::Red);
						rotateLeft(son->parent);
						brother = son->parent->childRight;
					}
					if (getColour(brother->childLeft) != Colour::Red && getColour(brother->childRight) != Colour::Red) 
					{
						setColour(brother, Colour::Red);
						son = son->parent;
					}
					else
					{
						if (getColour(brother->childRight) != Colour::Red) 
						{
							setColour(brother->childLeft, Colour::Black);
							setColour(brother, Colour::Red);
							rotateRight(brother);
							brother = son->parent->childRight;
						}

						setColour(brother, getColour(son->parent)); 
						setColour(son->parent, Colour::Black);
						setColour(brother->childRight, Colour::Black);
						rotateLeft(son->parent);		
						son = root;
					}
				}
				else
				{
					brother = son->parent->childLeft;
					if (getColour(brother) != Colour::Black)
					{
						setColour(brother, Colour::Black);
						setColour(son->parent, Colour::Red);
						rotateRight(son->parent);
						brother = son->parent->childLeft;
					}
					if (getColour(brother->childLeft) != Colour::Red && getColour(brother->childRight) != Colour::Red)
					{
						setColour(brother, Colour::Red);
						son = son->parent;
					}
					else
					{
						if (getColour(brother->childLeft) != Colour::Red)
						{
							setColour(brother->childRight, Colour::Black);
							setColour(brother, Colour::Red);
							rotateLeft(brother);
							brother = son->parent->childLeft;
						}

						setColour(brother, getColour(son->parent)); 
						setColour(son->parent, Colour::Black);
						setColour(brother->childLeft, Colour::Black);
						rotateRight(son->parent);		
						son = root;
					}
				}

			}
		}
		setColour(son, Colour::Black);
		delete buff;
	}
}

int CRedBlackTree::search(int value) // mozliwe jest zwracanie wskaznika na wyszukiwanego Node'a, jednak wymaga to upublicznienia struktury;
{
	if (root != nullptr)
		searchTree/*searchNode*/(value, root); 
	else
		return -1;
}

int CRedBlackTree::searchTree(int value, Node* temp) 
{
	if (temp->value == value)
		return value;
	else if (temp->value > value && temp->childLeft != &sentinel)
		searchTree(value, temp->childLeft);
	else if (temp->value < value && temp->childRight != &sentinel)
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
}



std::string CRedBlackTree::showColour(Node * temp)
{
	if (temp->colour == Colour::Black)
		return "B: ";
	else
		return "R: ";
}

CRedBlackTree::Node* CRedBlackTree::minNode(Node* temp)
{
	Node* buff = temp;
	while (buff->childLeft != &sentinel && buff->childLeft != nullptr)
		buff = buff->childLeft;
	return buff;
}

CRedBlackTree::Node* CRedBlackTree::getUncle(Node* temp)
{
	if (temp->parent->parent->childLeft == temp->parent)
		return temp->parent->parent->childRight;
	else
		return temp->parent->parent->childLeft;
}

CRedBlackTree::Node* CRedBlackTree::searchNode(int value, Node* temp)
{
	if (temp->value == value)
		return temp;
	else if (temp->value > value && temp->childLeft != &sentinel)
		searchNode(value, temp->childLeft);
	else if (temp->value < value && temp->childRight != &sentinel)
		searchNode(value, temp->childRight);
	else return nullptr;
}

CRedBlackTree::Node* CRedBlackTree::getSuccessor(Node* temp)
{
	if (temp != nullptr)
	{
		if (temp->childRight != &sentinel)
			return minNode(temp->childRight);
		else
		{
			Node* buff;
			buff = temp->parent;
			while (buff != nullptr && temp == buff->childRight)
			{
				temp = buff;
				buff = temp->parent;
			}
			return buff;
		}
	}
	else
		return nullptr;
}


void CRedBlackTree::setColour(Node * temp, Colour colour)
{
	temp->colour = colour;
}



CRedBlackTree::Colour CRedBlackTree::getColour(Node * temp)
{
	if (temp == &sentinel)
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

	if (p != &sentinel)
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


/*
//=======================================//
//				Remove for BST			 //
//=======================================//

//std::cout << temp->value;
if (temp != &sentinel)
{
Node* buff;
Node* son;

if (temp->childLeft == &sentinel || temp->childRight == &sentinel)
buff = temp;
else
buff = getSuccessor(temp);
if (buff->childLeft == &sentinel)
son = buff->childRight;
else
son = buff->childLeft;
if (son != &sentinel)
son->parent = buff->parent;
if (buff->parent == root)
{
root = son;
}
else
{
if (buff == buff->parent->childLeft)
buff->parent->childLeft = son;
else
buff->parent->childRight = son;
}
if (buff != temp)
temp->value = buff->value;
delete buff;
}
*/