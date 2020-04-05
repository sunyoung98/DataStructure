#pragma warning(disable: 4996)
#include "Manager.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <WTypes.h>
#include <oleauto.h>
using namespace std;

Manager::Manager()	//constructor
{
	bst = new NumberBST();
	queue = new Queue();
	ll = new LinkedList();

	arg_int1 = 0;
	arg_int2 = 0;

	int arr[10] = { 7, 3, 9, 1, 0, 2, 5, 4 ,8,6 };
	for (int i = 0; i < 10; i++) {
		NumberNode* node = new NumberNode();
		node->SetNumber(arr[i]);
		bst->Insert(node);
	}
}


Manager::~Manager()//destructor
{
	/* You must fill here */
	delete bst;
	delete queue;
	delete ll;
}

void Manager::run(const char * command)
{
	fin.open(command);
	flog.open("log.txt", ios::app);
	char* cmd = new char[40];

	while (!fin.eof())
	{
		/* You can write you code like example */

		fin.getline(cmd, 40);
		char * tmp = strtok(cmd, " ");

		if (strcmp(tmp, "LOAD") == 0) {
			if (LOAD()) printSuccessCode("LOAD");
			else printErrorCode(100);
		}
		else if (strcmp(tmp, "ADD") == 0) {
			if (ADD()) printSuccessCode("ADD");
			else printErrorCode(200);
		}
		else if (strcmp(tmp, "MOVE") == 0) {
			tmp = strtok(nullptr, " ");
			arg_int1 = atoi(tmp);
			if (MOVE()) printSuccessCode("MOVE");
			else printErrorCode(300);
		}
		else if (strcmp(tmp, "SAVE") == 0) {
			if (SAVE()) printSuccessCode("SAVE");
			else printErrorCode(400);
		}
		else if (strcmp(tmp, "SEARCH") == 0) {
			tmp = strtok(nullptr, " ");
			arg_int1 = atoi(tmp);
			if (!SEARCH()) printErrorCode(500);
		}
		else if (strcmp(tmp, "PRINT") == 0) {
			tmp = strtok(nullptr, " ");
			arg_str1 = tmp;
			if (strcmp(tmp, "EVENT_LIST") == 0) {
				tmp = strtok(nullptr, " ");
				arg_str2 = tmp;
			}
			if (!PRINT()) printErrorCode(600);
		}
		else if (strcmp(tmp, "COMPLETE") == 0) {
			tmp = strtok(nullptr, " ");
			arg_int1 = atoi(tmp);
			if (!COMPLETE()) printErrorCode(700);
		}
		else if (strcmp(tmp, "EXIT") == 0) {
			printSuccessCode("EXIT");
			EXIT();
		}
		else	printErrorCode(0);
	}

	return;
}

bool Manager::LOAD() {
	ifstream is;

	is.open("total_list_car.txt");
	char* cmd = new char[40];
	int count = 0;

	if (is.eof()) return false;

	while (!is.eof())
	{
		is.getline(cmd, 40);
		char* tmp = strtok(cmd, "\t");
		if (tmp == nullptr) break;

		CarNode* node = new CarNode();
		node->SetcarNum(atoi(tmp));
		tmp = strtok(nullptr, "\t");
		char* tmpstr = new char[40];
		strcpy(tmpstr, tmp);
		node->SetcarOwner(tmpstr);
		tmp = strtok(nullptr, "\t");
		node->Setstate(tmp[0]);

		ll->Insert(node);
		count++;
	}

	is.close();

	if (count == 0) return false;
	count = 0;

	is.open("event_list_car.txt", ios::app);
	cmd = new char[40];

	if (is.eof()) return false;

	CarBST* carBST = new CarBST();
	int idx = 0;
	int count2 = 0;

	while (!is.eof()) // 여러개의 BST를 넣는다
	{
		is.getline(cmd, 40);
		char* tmp = strtok(cmd, "\t");
		if (tmp == nullptr) break;

		if (idx != atoi(tmp)) { // 파일의 끝, BST 인덱스 변경 여부 확인, 만들어진 BST 넣고 새로운 BST 생성
			bst->Search(bst->currentNode)->SetBST(carBST); // 만들어진 BST 넣기
			bst->currentNode++;
			bst->totalList += count2;
			count2 = 0;
			carBST = new CarBST(); // 새로운 BST 생성
		}

		tmp = strtok(nullptr, "\t");
		CarNode* node = new CarNode();
		node->SetcarNum(atoi(tmp));
		tmp = strtok(nullptr, "\t");
		char* tmpstr = new char[40];
		strcpy(tmpstr, tmp);
		node->SetcarOwner(tmpstr);
		tmp = strtok(nullptr, "\t");
		node->Setstate(tmp[0]);
		carBST->Insert(node);

		count++;
		count2++;
	}

	bst->Search(bst->currentNode)->SetBST(carBST);
	bst->currentNode++;
	bst->totalList += count;

	is.close();

	if (count == 0) return false;
	count = 0;

	is.open("complete_list_car.txt", ios::app);
	cmd = new char[40];
	count = 0;

	if (is.eof()) return false;

	while (!is.eof())
	{
		is.getline(cmd, 40);
		char* tmp = strtok(cmd, "\t");
		if (tmp == nullptr) break;

		CarNode* node = new CarNode();
		node->SetcarNum(atoi(tmp));
		tmp = strtok(nullptr, "\t");
		char* tmpstr = new char[40];
		strcpy(tmpstr, tmp);
		node->SetcarOwner(tmpstr);
		tmp = strtok(nullptr, "\t");
		node->Setstate(tmp[0]);

		queue->Push(node);
		count++;
	}

	is.close();
	if (count == 0) return false;

	return true;
}

bool Manager::ADD() {
	ifstream is;

	is.open("car.txt", ios::app);
	char* cmd = new char[40];

	if (is.eof()) return false;
	
	// 중복 검사용 배열
	int numbers[1000];
	int cnt = 0;

	while (!is.eof())
	{
		is.getline(cmd, 40);
		char* tmp = strtok(cmd, "\t");	
		if (tmp == nullptr) break;

		// 중복 체크
		int cond = 0;
		for (int i = 0; i < cnt; i++) {
			if (numbers[i] == atoi(tmp)) cond = 1;
		}
		if (cond == 1) continue;

		CarNode* node = new CarNode();
		node->SetcarNum(atoi(tmp));
		tmp = strtok(nullptr, "\t");
		node->SetcarOwner(UTF8ToANSI(tmp));
		tmp = strtok(nullptr, "\t");	
		node->Setstate(tmp[0]);
		ll->Insert(node);
	}
	
	is.close();
	return true;
}

bool Manager::MOVE() {
	int count = 0;

	CarNode* cursor = ll->pHead;
	CarBST* carBST = new CarBST();
	while (true) {
		if (count == arg_int1) break;
		if (cursor == nullptr) return false;
		if (count + bst->totalList + 1 > 100) return false;

		if (cursor->Getstate() == 'Y') {
			CarNode* node = new CarNode();
			node->SetcarNum(cursor->GetcarNum());
			node->SetcarOwner(cursor->GetcarOwner());
			node->Setstate(cursor->Getstate());
			carBST->Insert(node);
			ll->Delete(cursor->GetcarNum());
			count++;
			
		}
		cursor = cursor->GetNext();
	}

	bst->Search(bst->currentNode)->SetBST(carBST);
	bst->currentNode++;
	bst->totalList += arg_int1;

	return true;
}

bool Manager::SAVE() {
	bool result = true;
	result = ll->Save();
	for (int i = 0; i < bst->currentNode; i++) {
		bst->Search(i)->GetBST()->index = i;
		result = bst->Search(i)->GetBST()->Save();	
	}
	result = queue->Save();

	return result;
}

bool Manager::SEARCH() {
	CarNode* node = ll->Search(arg_int1);
	if (node != nullptr) {
		string str = to_string(node->GetcarNum()) + " " + node->GetcarOwner() + " " + node->Getstate();
		printSuccessCode_2("SEARCH", str);
		return true;
	}
	
	for (int i = 0; i < bst->currentNode; i++) {
		node = bst->Search(i)->GetBST()->Search(arg_int1);
		if (node != nullptr) {
			string str = to_string(node->GetcarNum()) + " " + node->GetcarOwner() + " " + node->Getstate();
			printSuccessCode_2("SEARCH", str);
		}
		return true;
	}

	node = queue->Search(arg_int1);
	if (node != nullptr) {
		string str = to_string(node->GetcarNum()) + " " + node->GetcarOwner() + " " + node->Getstate();
		printSuccessCode_2("SEARCH", str);
		return true;
	}	

	return false;
}

bool Manager::PRINT() {
	if (strcmp(arg_str1.c_str(), "TOTAL_LIST") == 0) {
		if (ll->size == 0) return false;
		cout << "======== PRINT ========" << endl;
		flog << "======== PRINT ========" << endl;
		ll->Print();
		cout << "=======================" << endl << endl;
		flog << "=======================" << endl << endl;
	}
	else if (strcmp(arg_str1.c_str(), "EVENT_LIST") == 0) {
		if (bst->currentNode == 0) return false;
		cout << "======== PRINT ========" << endl;
		flog << "======== PRINT ========" << endl;	
		for (int i = 0; i < bst->currentNode; i++) {
			bst->Search(i)->GetBST()->Print(arg_str2.c_str());
		}
		cout << "=======================" << endl << endl;
		flog << "=======================" << endl << endl;
	}
	else {
		if (queue->size == 0) return false;
		cout << "======== PRINT ========" << endl;
		flog << "======== PRINT ========" << endl;
		queue->Print();
		cout << "=======================" << endl << endl;
		flog << "=======================" << endl << endl;
	}
	return true;
}

bool Manager::COMPLETE() {
	for (int i = 0; i < bst->currentNode; i++) {
		CarNode* node = bst->Search(i)->GetBST()->Search(arg_int1);
		if (node != nullptr) {
			CarNode* newNode = new CarNode();
			newNode->SetcarNum(node->GetcarNum());
			newNode->SetcarOwner(node->GetcarOwner());
			newNode->Setstate('C');
			queue->Push(newNode);

			bst->Search(i)->GetBST()->Delete(arg_int1);
			bst->totalList--;

			string str = to_string(newNode->GetcarNum()) + " " + newNode->GetcarOwner() + " C";
			printSuccessCode_2("COMPLETE", str);

			return true;
		}
	}

	return false;
}

void Manager::EXIT() {
	try {
		fin.close();
		flog.close();
		exit(0);
	}
	catch (exception e) {
		printErrorCode(0);
	}

}


void Manager::printErrorCode(int n) {
	//ERROR CODE PRINT 
	flog << "======== ERROR ========" << endl;
	flog << n << endl;
	flog << "=======================" << endl << endl;

	cout << "======== ERROR ========" << endl;
	cout << n << endl;
	cout << "=======================" << endl << endl;
}

void Manager::printSuccessCode(const char * cmdname) {
	//SUCCESS CODE PRINT
		flog << "======== " << cmdname << " ========" << endl;
		flog << "Success" << endl;
		flog << "=======================" << endl << endl;

		cout << "======== " << cmdname << " ========" << endl;
		cout << "Success" << endl;
		cout << "=======================" << endl << endl;
}

void Manager::printSuccessCode_2(const char* cmdname, string str) {
	flog << "======== " << cmdname << " ========" << endl;
	flog << str << endl;
	flog << "=======================" << endl << endl;

	cout << "======== " << cmdname << " ========" << endl;
	cout << str << endl;
	cout << "=======================" << endl << endl;
}

char* Manager::UTF8ToANSI(const char* pszCode)
{
	BSTR    bstrWide;
	char* pszAnsi;
	int     nLength;

	nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, lstrlen(pszCode) + 1, NULL, NULL);
	bstrWide = SysAllocStringLen(NULL, nLength);

	MultiByteToWideChar(CP_UTF8, 0, pszCode, lstrlen(pszCode) + 1, bstrWide, nLength);

	nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
	pszAnsi = new char[nLength];

	WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
	SysFreeString(bstrWide);

	return pszAnsi;

}