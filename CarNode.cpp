#include "CarNode.h"
#include<cstring>

CarNode::CarNode()	//constructor
{
	carNumber = 0;
	name = nullptr;
	state = ' ';

	pLeft = nullptr;
	pNext = nullptr;
	pRight = nullptr;
}

CarNode::~CarNode()//destructor
{
	
}

int CarNode::GetcarNum()
{
	return carNumber;
}

char* CarNode::GetcarOwner()
{
	return name;
}

char CarNode::Getstate()
{
	return state;
}

CarNode* CarNode::GetLeft()
{
	return pLeft;
}

CarNode* CarNode::GetRight()
{
	return pRight;
}

CarNode* CarNode::GetNext()
{
	return pNext;
}

void CarNode::SetcarNum(int carNum)
{
	this->carNumber = carNum;
}

void CarNode::SetcarOwner(char* carOwner)
{
	this->name = carOwner;
}

void CarNode::Setstate(char state)
{
	this->state = state;
}

void CarNode::SetLeft(CarNode* node)
{
	this->pLeft = node;
}

void CarNode::SetRight(CarNode* node)
{
	this->pRight = node;
}

void CarNode::SetNext(CarNode* node)
{
	this->pNext = node;
}
