#include "LinkedList.h"
#include <fstream>
#include <string>

LinkedList::LinkedList()//constructor
{
	pHead = nullptr;
	pTail = nullptr;
	size = 0;
	flog.open("log.txt", ios::app);
}

LinkedList::~LinkedList()//destructor
{
	/* You must fill here */
	while (pHead != nullptr) {
		CarNode* temp = pHead;
		pHead = pHead->GetNext();
		delete temp;
	}

	flog.close();
}

void LinkedList::Insert(CarNode* node)
{
	if (pHead == nullptr)
		pHead = pTail = node;
	else {
		pTail->SetNext(node);
		pTail = node;
	}
	size++;
}

CarNode* LinkedList::Search(int car)
{
	CarNode* cursor;
	cursor = pHead;
	while (cursor!=nullptr) {		
		if (cursor->GetcarNum() == car) return cursor;
		cursor = cursor->GetNext();
	}
	return NULL;
}

bool LinkedList::Print()
{
	CarNode* cursor;
	cursor = pHead;
	while (cursor!=nullptr) {
		cout << cursor->GetcarNum() << " " << cursor->GetcarOwner() << " " << cursor->Getstate() << "\n";
		flog << cursor->GetcarNum() << " " << cursor->GetcarOwner() << " " << cursor->Getstate() << "\n";
		cursor = cursor->GetNext();
	}
	return 0;
}

bool LinkedList::Save()
{
	string filePath = "total_list_car.txt";

	ofstream writeToFile;
	writeToFile.open(filePath);
	CarNode* cursor;
	cursor = pHead;
	
	if (pHead == nullptr) return false;

	while (cursor != nullptr) {
		string tmp = to_string(cursor->GetcarNum()) + "\t" + cursor->GetcarOwner() + "\t" + cursor->Getstate() + "\n";
		writeToFile.write(tmp.c_str(), tmp.size());
		cursor = cursor->GetNext();
	}

	writeToFile.close();

	return true;
}

bool LinkedList::Delete(int Carnum)
{
	CarNode *head_ptr = pHead;
	CarNode* temp = head_ptr;
	while (head_ptr != nullptr) {
		if (head_ptr->GetcarNum() == Carnum) {
			break;
		}
		else {
			temp = head_ptr;
			head_ptr = head_ptr->GetNext();
		}
	}
	if (head_ptr == nullptr)
		return false;
	else{
		temp->SetNext(head_ptr->GetNext());	// 삭제하려는 노드의 이전노드가 삭제될 노드의 다음 노드를 가리키도록 한다.
		if (head_ptr == pHead) pHead = temp->GetNext();
		if (head_ptr == pTail) pTail = temp;
		size--;
		return true;
	}
}
