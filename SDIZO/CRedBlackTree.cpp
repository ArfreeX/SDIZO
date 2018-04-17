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

void CRedBlackTree::deleteTree(Node* temp) // rekurencyjne niszczenie drzewa
{
	if (temp != &sentinel && temp != nullptr)
	{
		if (temp->childLeft != &sentinel)
			deleteTree(temp->childLeft);
		if (temp->childRight != &sentinel)
			deleteTree(temp->childRight);
		delete temp;
	}
}

void CRedBlackTree::add(int value)
{
	if (root == nullptr || root == &sentinel) // gdy drzewo jest puste dodajemy element 'na' roota i konczymy
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
		while (temp != &sentinel) // dopoki nie dojdziemy do wezla straznika powtarzamy poszukiwanie miejsca na nowy wezel
		{
			buff = temp;
			if (temp->value > value) // sprawdzenie warunku dodawania do drzewa bst
				temp = temp->childLeft;
			else
				temp = temp->childRight;
		}

		temp = new Node(value); // dodajemy nowy wezel w miejsce straznika
		temp->childLeft = &sentinel; // przepinamy straznika jako dzieci
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
	Node* temp = nullptr;
	temp = searchNode(value, root); // wyszukujemy adres wezla ktory mamy usunac [ rekurencyjnie ]

	if ( temp != &sentinel && temp != nullptr) // jezeli wezel istnieje przechodzimy dalej
	{
		Node* buff, *son, *brother;

		if (temp->childLeft == &sentinel || temp->childRight == &sentinel) // sytuacja gdy wezel ma tylko 0 lub 1 dziecko przypadki 1 & 2
			buff = temp;
		else
			buff = getSuccessor(temp);		// gdy wezel posiada dwojke dzieci pobieramy nastepce przypadki 3 & 4

		if (buff->childLeft == &sentinel) 
			son = buff->childRight;
		else
			son = buff->childLeft;
		son->parent = buff->parent; // przypisujemy synowi nowego ojca

		if (buff->parent == nullptr)
		{
			root = son;
		}
		else if (buff == buff->parent->childLeft) // version3. updt
			buff->parent->childLeft = son; // przypisujemy ojcu syna, uzupelniamy polaczenie
		else
			buff->parent->childRight = son; // -||-
		if (buff != temp)
			temp->value = buff->value; // dla przypadkow 3 & 4 przepisujemy wartosc
		if (getColour(buff) != Colour::Red) // jezeli usuwany wezel jest czerwony to konczymy poniewaz nie zaburzymy warunkow drzewa RBT
		{
			while (son != root && getColour(son) == Colour::Black) // powtarzamy az do osiagniecia korzenia drzewa badz wezla koloru czerwonego
			{
				if (son != son->parent->childRight) // syn jest lewym dzieckiem
				{
					brother = son->parent->childRight;
					if (getColour(brother) != Colour::Black) // przypadek 1 - brat jest czerwony
					{
						setColour(brother, Colour::Black);
						setColour(son->parent, Colour::Red);
						rotateLeft(son->parent);
						brother = son->parent->childRight;
					}
					if (getColour(brother->childLeft) != Colour::Red && getColour(brother->childRight) != Colour::Red) // brat wezla posiada 2 czarnych synow
					{
						setColour(brother, Colour::Red); // zamiana koloru 
						son = son->parent; // przechodzimy na wyzszy poziom drzewa
					}
					else
					{
						if (getColour(brother->childRight) != Colour::Red)  // jezeli prawe dziecko czarne
						{
							setColour(brother->childLeft, Colour::Black);
							setColour(brother, Colour::Red);
							rotateRight(brother);
							brother = son->parent->childRight; // przygotowujemy wezly do rotacji w lewo
						}

						setColour(brother, getColour(son->parent)); 
						setColour(son->parent, Colour::Black);
						setColour(brother->childRight, Colour::Black);
						rotateLeft(son->parent);		
						son = root; // warunek konczacy petle
					}
				}
				else // przypadki lustrzane
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
						son = root; // zakanczamy petle
					}
				}

			}
		}
		setColour(son, Colour::Black); // syn dostaje kolor czarny
		delete buff;		// zwalniamy pamiec
		buff = nullptr;		// przepinamy wskaznik na nullptr ( pozwala uniknac bledow )
	}
}

int CRedBlackTree::search(int value) // mozliwe jest zwracanie wskaznika na wyszukiwanego Node'a, jednak wymaga to upublicznienia struktury;
{
	if (root != nullptr)
		return searchTree/*searchNode*/(value, root); 
	else
		return -1;
}

int CRedBlackTree::searchTree(int value, Node* temp)  // rekurencyjne wyszukiwanie w drzewie
{
	if (temp->value == value) 
		return value;
	else if (temp->value > value && temp->childLeft != &sentinel)
		return searchTree(value, temp->childLeft);
	else if (temp->value < value && temp->childRight != &sentinel)
		return searchTree(value, temp->childRight);
	else return -1;
}

void CRedBlackTree::checkRBT(Node* temp)
{
	Node* uncle = nullptr;
	Node* tParent = nullptr;
	Node* gParent = nullptr;
	while (temp != root && getColour(temp) == Colour::Red && getColour(temp->parent) == Colour::Red) // sprawdzenie warunku drzewa RBT
	{
		uncle = getUncle(temp);
		tParent = temp->parent;
		gParent = tParent->parent;
		if (tParent == gParent->childLeft) // przypadki "normalne"
		{
			if (getColour(uncle) == Colour::Red) // jezeli wujek czerwony to zamieniamy kolory
			{
				setColour(uncle, Colour::Black);
				setColour(tParent, Colour::Black);
				setColour(gParent, Colour::Red);
				setColour(root, Colour::Black);
				temp = gParent; // przechodzimy poziom wyzej
			}
			else // wujek jest czarny
			{
				if (temp == tParent->childRight) // w przypadku 'wezyka' rootujemy w lewo				O					
				{								 //													   / \   
					rotateLeft(tParent);		 //													  O   O 
					temp = tParent;				 //													   \ 
					tParent = temp->parent;      //														O
				}
				rotateRight(gParent);		 	 // rootujemy w prawo 
				switchColour(tParent);			 // zmieniamy kolory na przeciwne
				switchColour(gParent);
				temp = tParent;				   	 // sprawdzamy warunek RBT poziom wyzej
			}
		}
		else // przypadki lustrzane
		{
			if (getColour(uncle) == Colour::Red) // -||-
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



void CRedBlackTree::rotateLeft(Node * temp) // komentarze analogicznie jak dla rotateRight(*)
{
	Node* rChild = temp->childRight;
	Node* tParent;
	if (rChild != &sentinel)
	{
		tParent = temp->parent;
		temp->childRight = rChild->childLeft;
		if (temp->childRight != &sentinel) // zmiana z nullptr
			temp->childRight->parent = temp;
		rChild->childLeft = temp;
		rChild->parent = tParent;
		temp->parent = rChild;
		if (tParent != &sentinel  && tParent != nullptr)
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
	Node* tParent;

	if (lChild != &sentinel)
	{
		tParent = temp->parent;
		temp->childLeft = lChild->childRight;
		if (temp->childLeft != &sentinel)	// przepinamy potomka o ile istnieje
			temp->childLeft->parent = temp;
		lChild->childRight = temp;		// rodzic jako prawe dziecko po rotacji
		lChild->parent = tParent;		// przepinamy rodzica
		temp->parent = lChild;
		if (tParent != &sentinel  && tParent != nullptr)
		{
			if (temp == tParent->childLeft)	// przypisujemy do rodzica nowe dziecko, zaleznie od pozycji pierwotnego wezla
				tParent->childLeft = lChild;
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
	if (temp != nullptr)
	{

		if (temp->value == value)
			return temp;
		else if (temp->value > value && temp->childLeft != &sentinel)
			return searchNode(value, temp->childLeft);
		else if (temp->value < value && temp->childRight != &sentinel)
			return searchNode(value, temp->childRight);
		else
			return nullptr;
	}
	else return nullptr;
}

CRedBlackTree::Node* CRedBlackTree::getSuccessor(Node* temp)
{
	if (temp != nullptr)
	{
		if (temp->childRight != &sentinel)
			return minNode(temp->childRight); // pobieramy najmniejszy wezel z prawego dziecka
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
{																	   //stackoverflow for too many arguments ( 100 000);
	std::string s, cr, cl, cp;
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;

	if (p != &sentinel && p!= nullptr)
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