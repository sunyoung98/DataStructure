#pragma once
#include "CarNode.h"
#include <fstream>

class LinkedList
{
public:
	CarNode* pHead;
	CarNode* pTail;

	LinkedList();
	~LinkedList();

	void Insert(CarNode * node);	//LOAD, ADD
	CarNode * Search(int car);		//SEARCH
	bool Print();	//PRINT
	bool Save();	//SAVE
	bool Delete(int Carnum);

	int size;
	ofstream flog;
};
