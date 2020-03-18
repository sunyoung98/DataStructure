#pragma once
#include "LinkedList.h"
#include "NumberBST.h"
#include "Queue.h"
#include<utility>
#include <fstream>
#include <string>


class Manager
{
public:
	LinkedList * ll;
	NumberBST * bst;
	Queue * queue;
	ifstream fin;
	ofstream flog;
	string command;
	int arg_int1;
	int arg_int2;
	string arg_str1;
	string arg_str2;

public:
	Manager();
	~Manager();

	void run(const char * command);
	bool LOAD();
	bool ADD();
	bool MOVE();
	bool SAVE();
	bool SEARCH();
	bool PRINT();
	bool COMPLETE();
	void EXIT();

	void printErrorCode(int n);
	void printSuccessCode(const char * cmdname);

	void printSuccessCode_2(const char* cmdname, string str);
	char* UTF8ToANSI(const char* pszCode);

};
