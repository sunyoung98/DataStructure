#pragma once
#include "CarNode.h"
#include <iostream>
#include <fstream>// header file declare
using namespace std;
class CarBST
{
public:
	CarNode * root;	

public:
	CarBST();
	~CarBST();

	CarNode* Empty(CarNode* root);
	void		Insert(CarNode * node);			// LOAD, MOVE
	CarNode *	Delete(int num);				// COMPLETE
	CarNode* remove(CarNode* parent, CarNode* root, int num);
	CarNode *	Search(int num);				// ADD, COMPLETE, SEARCH
	bool		Print(const char * order);		// PRINT
	bool		Save();							// SAVE
	void		PreorderSave(CarNode* node);
	void		Inorder(CarNode *node);
	void		Preorder(CarNode *node);
	void		Postorder(CarNode *node);
	void		levelorder();
	void		iterativeInorder();
	void		iterativePreorder();
	void		iterativePostorder();
	CarNode* find(CarNode* node, int num);
	CarNode* findMin(CarNode* node);
	CarNode* findMax(CarNode* node);



	ofstream flog;
	int index;
};

