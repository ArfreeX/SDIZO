#include "stdafx.h"



CAVLTree::CAVLTree()
{
	root = nullptr;
}


CAVLTree::~CAVLTree()
{
	deleteTree(root);
}

void CAVLTree::deleteTree(Node* temp)
{
	if (temp != nullptr)
	{
		if (temp->childLeft != nullptr)
			deleteTree(temp->childLeft);
		if (temp->childRight != nullptr)
			deleteTree(temp->childRight);
		delete temp;
	};
}

void CAVLTree::add(int value)
{
	if (root == nullptr)
	{
		root = new Node(value);
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
		balanceTree(temp);
	}

}

void CAVLTree::balanceTree(Node* temp)
{
	Node* par, *gpar; // parent & grandparent
	bool stop = false;
	par = temp->parent;
	if (par->bf != 0) // rodzic byl "dopuszczalnie" niezbalansowany -> teraz jest zbalansowany - konczymy
		par->bf = 0;
	else
	{
		if (par->childLeft == temp) // dodajemy wezel w miejsce lewego dziecka 
			par->bf = 1;
		else
			par->bf = -1;
		gpar = par->parent; // przypisujemy dziadka
		while (gpar != nullptr && !stop) // wykonujemy dopoki dziadek istnieje  ( operacje w petli identyczne jak dla rodzica wyzej )
		{
			if (gpar->bf) // szukamy wezla ktory jest niezbalansowany
			{
				stop = true;
			}
			else {
				if (gpar->bf == 0)
				{
					if (gpar->childLeft == par)
						gpar->bf = 1;
					else
						gpar->bf = -1;
				}
				par = gpar;
				gpar = gpar->parent;
			}
		}
		if (stop) // jezeli znaleziono niezbalansowany wezel to wykonujemy jego naprawe
			if (gpar->bf != -1)
			{
				if (gpar->childRight != par)
				{
					if (par->bf == -1)
						rotateDoubleLeft(gpar);//lr
					else
						rotateLeft(gpar);//ll
				}
				else
				{
					gpar->bf = 0;
				}
			}
			else // przypadki lustrzane
			{
				if (gpar->childLeft == par)
					gpar->bf = 0;
				else
				{
					if (par->bf == 1)
						rotateDoubleRight(gpar);//rl
					else
						rotateRight(gpar);//rr
				}
			}
	}
}
void CAVLTree::remove(int value)
{
	Node* temp = nullptr;
	temp = searchNode(value, root);
	if (temp != nullptr)
	{
		removeNode(temp);
	}
}

void CAVLTree::removeNode(Node* temp)
{
	Node* buff, *par, *xbuff; // wskazniki pomocnicze
	bool test = false;
	if (temp->childLeft != nullptr && temp->childRight != nullptr)
	{
		par = getSuccessor(temp);
		removeNode(getSuccessor(temp));
		test = false;
	}
	else
	{
		if (temp->childLeft != nullptr)
		{
			par = temp->childLeft;
			temp->childLeft = nullptr;
		}
		else
		{
			par = temp->childRight;
			temp->childRight = nullptr;
		}
		temp->bf = 0;
		test = true;
	}
	if (par != nullptr)
	{
		par->parent = temp->parent;
		par->childLeft = temp->childLeft;
		if (par->childLeft != nullptr)
			par->childLeft->parent = par;
		par->childRight = temp->childRight;
		if (par->childRight != nullptr)
			par->childRight->parent = par;
		par->bf = temp->bf;
	}
	if (temp->parent != nullptr)
	{
		if (temp->parent->childLeft == temp)
			temp->parent->childLeft = par;
		else
			temp->parent->childRight = par;
	}
	else
		root = par;
	if (test)
	{
		xbuff = par;
		par = temp->parent;
		while (par != nullptr && test)
		{
			if (par->bf == 0)
			{
				if (par->childLeft == xbuff)
					par->bf = -1;
				test = false;
	
			}
			else
			{
				if (((par->bf == 1) && (par->childLeft == xbuff)) || ((par->bf == -1) && (par->childRight == xbuff)))
				{
					par->bf = 0;
					xbuff = par;
					par = par->parent;
				}
				else
				{
					if (par->childLeft == xbuff)
						buff = par->childRight;
					else
						buff = par->childLeft;
					if (buff->bf != 0)
					{
						if (par->bf == 1)
							rotateLeft(par);
						else
							rotateRight(par);
						test = false;
					}
					else if (par->bf == buff->bf)
					{
						if (par->bf == 1)
							rotateLeft(par);
						else
							rotateRight(par);
						xbuff = buff;
						par = buff->parent;
					}
					else
					{
						if (par->bf == 1)
							rotateDoubleLeft(par);
						else
							rotateDoubleRight(par);
						xbuff = par->parent;
						par = xbuff->parent;
					}

				}

			}
		}
	}

}
int CAVLTree::search(int value) // mozliwe jest zwracanie wskaznika na wyszukiwanego Node'a, jednak wymaga to upublicznienia struktury;
{
	if (root != nullptr)
		return searchTree/*searchNode*/(value, root);
	else
		return -1;
}

int CAVLTree::searchTree(int value, Node* temp)
{
	if (temp->value == value)
		return value;
	else if (temp->value > value && temp->childLeft != nullptr)
		return searchTree(value, temp->childLeft);
	else if (temp->value < value && temp->childRight != nullptr)
		return searchTree(value, temp->childRight);
	else return -1;
}

void CAVLTree::rotateLeft(Node* temp)
{
	if (temp != nullptr) {
		Node* par, *buff;
		buff = temp->childLeft;
		par = temp->parent;
		temp->childLeft = buff->childRight; // buff->nullptr [ child cos tam ]
		if (temp->childLeft != nullptr)
			temp->childLeft->parent = temp;
		buff->childRight = temp;
		buff->parent = par;
		temp->parent = buff;
		if (par != nullptr)
		{
			if (par->childLeft == temp)
				par->childLeft = buff;
			else
				par->childRight = buff;
		}
		else
			root = buff;
		if (buff->bf == 1)
		{
			temp->bf = 0;
			buff->bf = 0;
		}
		else
		{
			temp->bf = 1;
			buff->bf = -1;
		}
	}
}

void CAVLTree::rotateRight(Node* temp)
{
	if (temp != nullptr)
	{
		Node* par, *buff;
		buff = temp->childRight;
		par = temp->parent;
		temp->childRight = buff->childLeft; // buff->nullptr [ child cos tam ]
		if (temp->childRight != nullptr)
			temp->childRight->parent = temp;
		buff->childLeft = temp;
		buff->parent = par;
		temp->parent = buff;
		if (par != nullptr)
		{
			if (par->childLeft == temp)
				par->childLeft = buff;
			else
				par->childRight = buff;
		}
		else
			root = buff;
		if (buff->bf == -1)
		{
			temp->bf = 0;
			buff->bf = 0;
		}
		else
		{
			temp->bf = -1;
			buff->bf = 1;
		}
	}
}

void CAVLTree::rotateDoubleLeft(Node* temp)
{
	Node* buff, *xbuff, *par;
	buff = temp->childLeft;
	xbuff = buff->childRight;
	par = temp->parent;
	buff->childRight = xbuff->childLeft;
	if (buff->childRight != nullptr)
		buff->childRight->parent = buff;
	temp->childLeft = xbuff->childRight;
	if (temp->childLeft != nullptr)
		temp->childLeft->parent = temp;
	xbuff->childRight = temp;
	xbuff->childLeft = buff;
	temp->parent = xbuff;
	buff->parent = xbuff;
	xbuff->parent = par;
	if (par != nullptr) // 13
	{
		if (par->childLeft == temp)
			par->childLeft = xbuff;
		else
			par->childRight = xbuff;
	}
	else
		root = xbuff;
	if (xbuff->bf == 1)
		temp->bf = -1;
	else
		temp->bf = 0;
	if (xbuff->bf == -1)
		buff->bf = 1;
	else
		buff->bf = 0;
	xbuff->bf = 0;
}


void CAVLTree::rotateDoubleRight(Node* temp)
{
	Node* buff, *xbuff, *par;
	buff = temp->childRight;
	xbuff = buff->childLeft;
	par = temp->parent;
	buff->childLeft = xbuff->childRight;
	if (buff->childLeft != nullptr)
		buff->childLeft->parent = buff;
	temp->childRight = xbuff->childLeft;
	if (temp->childRight != nullptr)
		temp->childRight->parent = temp;
	xbuff->childLeft = temp;
	xbuff->childRight = buff;
	temp->parent = xbuff;
	buff->parent = xbuff;
	xbuff->parent = par;
	if (par != nullptr) // 13
	{
		if (par->childLeft == temp)
			par->childLeft = xbuff;
		else
			par->childRight = xbuff;
	}
	else
		root = xbuff;
	if (xbuff->bf == -1)
		temp->bf = 1;
	else
		temp->bf = 0;
	if (xbuff->bf == 1)
		buff->bf = -1;
	else
		buff->bf = 0;
	xbuff->bf = 0;
}

CAVLTree::Node* CAVLTree::minNode(Node* temp)
{
	Node* buff = temp;
	while (buff->childLeft != nullptr && buff->childLeft != nullptr)
		buff = buff->childLeft;
	return buff;
}

CAVLTree::Node* CAVLTree::getUncle(Node* temp)
{
	if (temp->parent->parent->childLeft == temp->parent)
		return temp->parent->parent->childRight;
	else
		return temp->parent->parent->childLeft;
}

CAVLTree::Node* CAVLTree::searchNode(int value, Node* temp)
{
	if (temp != nullptr)
	{
		if (temp != nullptr && temp->value == value)
			return temp;
		else if (temp->value > value && temp->childLeft != nullptr)
			return searchNode(value, temp->childLeft);
		else if (temp->value < value && temp->childRight != nullptr)
			return searchNode(value, temp->childRight);
		else 
			return nullptr;
	}
	else
		return nullptr;
}

CAVLTree::Node* CAVLTree::getSuccessor(Node* temp)
{
	if (temp != nullptr)
	{
		if (temp->childRight != nullptr)
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

int CAVLTree::height(Node* temp)
{
	int lHeight = -1;
	int rHeight = -1;

	if (temp->childLeft != nullptr)
		lHeight = height(temp->childLeft);
	if (temp->childRight != nullptr)
		rHeight = height(temp->childRight);
	return max(lHeight, rHeight) + 1;
}

void CAVLTree::printTree()
{
	printTree("", "", root);
}

void CAVLTree::printTree(std::string sp, std::string sn, Node* p) // source: http://eduinf.waw.pl/inf/alg/001_search/0113.php
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
		std::cout << s << sn << "( V:" << p->value << ", H:" << height(p) << " )" << std::endl;

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
if (temp != nullptr)
{
Node* buff;
Node* son;

if (temp->childLeft == nullptr || temp->childRight == nullptr)
buff = temp;
else
buff = getSuccessor(temp);
if (buff->childLeft == nullptr)
son = buff->childRight;
else
son = buff->childLeft;
if (son != nullptr)
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
