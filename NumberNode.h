#pragma once
#include "CarBST.h"

class NumberNode
{
private:
	int number;
	CarBST * bst;
	NumberNode * pLeft;			// BST Left Pointer
	NumberNode * pRight;		// BST Right Pointer

public:
	NumberNode();
	~NumberNode();

	int			GetNumber();						// Get Number
	CarBST *		GetBST();						// Get Car BST
	NumberNode *	GetLeft();						// Get BST Left Pointer
	NumberNode *	GetRight();						// Get BST Right Pointer

	void			SetNumber(int num);				// Set Alphabet
	void			SetLeft(NumberNode * node);		// Set BST Left Pointer
	void			SetRight(NumberNode * node);	// Set BST Right Pointer
	void 			SetBST(CarBST * node);			// Set Car BST
};