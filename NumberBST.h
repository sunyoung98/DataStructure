#pragma once
#include "NumberNode.h"
#include <iostream>


class NumberBST
{
private:
	NumberNode * root;
	int nodeCnt;

public:
	NumberBST();
	~NumberBST();

	NumberNode* Empty(NumberNode* root);
	void		Insert(NumberNode * node);			// LOAD, MOVE
	NumberNode *	Delete(int num);				// COMPLETE
	NumberNode *	Search(int num);				// ADD, COMPLETE, SEARCH
	NumberNode* remove(NumberNode* parent, NumberNode* root, int num);
	bool		Print(char * BST);					// PRINT
	bool		Save();								// SAVE
	void		PreorderSave(NumberNode* node);
	NumberNode* find(NumberNode* node, int num);
	NumberNode* findMin(NumberNode* node);
	NumberNode* findMax(NumberNode* node);
	void		Inorder(NumberNode *node);
	void		Preorder(NumberNode *node);
	void		Postorder(NumberNode *node);
	int			getCnt();
	void		setCnt(int cnt);

	int			totalList;
	int			currentNode;

	ofstream flog;
};