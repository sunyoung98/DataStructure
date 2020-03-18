#include "NumberNode.h"


NumberNode::NumberNode()//constructor
{
	number = 0;
	bst = nullptr;
	pLeft = nullptr;
	pRight = nullptr;
}

NumberNode::~NumberNode()//destructor
{
	/* You must fill here */
	if (GetBST() != nullptr) delete GetBST();
}

int NumberNode::GetNumber()
{
	return number;
}

CarBST* NumberNode::GetBST()
{
	return bst;
}

NumberNode* NumberNode::GetLeft()
{
	return pLeft;
}

NumberNode* NumberNode::GetRight()
{
	return pRight;
}

void NumberNode::SetNumber(int num)
{
	this->number = num;
}

void NumberNode::SetLeft(NumberNode* node)
{
	this->pLeft = node;
}

void NumberNode::SetRight(NumberNode* node)
{
	this->pRight = node;
}

void NumberNode::SetBST(CarBST* node)
{
	this->bst = node;
}
