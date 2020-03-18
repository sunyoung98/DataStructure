#pragma once
#include "CarNode.h"
#include <fstream>
class Queue
{
public: 		// public member funciton
	Queue();	
	~Queue();
	CarNode* pHead;							// member variable
	CarNode* pTail;
	int size;
	void		Push(CarNode * node);			// LOAD
	CarNode *	Pop();							
	CarNode *	Search(int num);				// SEARCH
	bool		Print();						// PRINT
	bool		Save();

	ofstream flog;
};

