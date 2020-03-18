#pragma once
#include <iostream>

using namespace std;

class CarNode
{
private:
	int carNumber;
	char * name;
	char state;

	CarNode * pLeft;	// BST Left Pointer
	CarNode * pRight;	// BST Right Pointer
	CarNode * pNext;	// Queue Next Pointer, LinkedList Next Pointer


public:
	CarNode();
	~CarNode();

	int GetcarNum();		// Get car number
	char * GetcarOwner();	// Get car owner
	char Getstate();		// Get state

	CarNode * GetLeft();	// Get BST Left Pointer
	CarNode * GetRight();	// Get BST Right Pointer
	CarNode * GetNext();	// Get Queue Next Pointer

	void SetcarNum(int carNum);			// Set car number
	void SetcarOwner(char * carOwner);	// Set car owner
	void Setstate(char state);			// Set car state
	void SetLeft(CarNode * node);		// Set BST Left Pointer
	void SetRight(CarNode * node);		// Set BST Right Pointer
	void SetNext(CarNode * node);		// Set Queue Next Pointer
};

