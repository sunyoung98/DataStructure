#include "Queue.h"
#include <fstream>
#include <string>

Queue::Queue()//constructor
{
	pHead = pTail = nullptr;
	size = 0;
	flog.open("log.txt", ios::app);
}


Queue::~Queue()//destructor
{
	flog.close();
}


void Queue::Push(CarNode* node)
{
	if (this->size == 0) {
		this->pHead = this->pTail = node;
	}
	else {
		this->pTail->SetNext(node);
		this->pTail = node;
	}
	this->size++;
}

CarNode* Queue::Pop()
{
	CarNode* result = new CarNode();
	result->SetcarNum(pHead->GetcarNum());
	result->SetcarOwner(pHead->GetcarOwner());
	result->Setstate(pHead->Getstate());
	CarNode* temp = pHead;
	pHead = pHead->GetNext();
	delete temp;
	size--;
	return result;
}

CarNode* Queue::Search(int num)
{
	CarNode* cursor;
	cursor = pHead;
	while (cursor != nullptr) {
		if (cursor->GetcarNum() == num) return cursor;
		cursor = cursor->GetNext();
	}
	return NULL;
}

bool Queue::Print()
{
	if (size == 0) {
		cout << "SIZE = 0 " << endl;
		flog << "SIZE = 0 " << endl;
		return false;
	}

	CarNode* cursor;
	cursor = pHead;
	while (cursor != nullptr) {
		cout << cursor->GetcarNum() << " " << cursor->GetcarOwner() << " " << cursor->Getstate() << endl;
		flog << cursor->GetcarNum() << " " << cursor->GetcarOwner() << " " << cursor->Getstate() << endl;
		cursor = cursor->GetNext();
	}
	return true;

}

bool Queue::Save()
{
	if (size == 0) return false;
	
	string filePath = "complete_list_car.txt";

	ofstream writeToFile;
	writeToFile.open(filePath);

	CarNode* cursor;
	cursor = pHead;
	while (cursor != nullptr) {
		string tmp = to_string(cursor->GetcarNum()) + "\t" + cursor->GetcarOwner() + "\t" + cursor->Getstate() + "\n";
		writeToFile.write(tmp.c_str(), tmp.size());
		cursor = cursor->GetNext();
	}

	writeToFile.close();

	return true;

}
