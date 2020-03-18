#include "CarBST.h"
#include <queue>
#include <stack>
#include <string>
#include <fstream>

CarBST::CarBST()//constructor
{
	root = nullptr;
	index = 0;
	flog.open("log.txt", ios::app);
}


CarBST::~CarBST()//destructor
{
	/* You must fill here */
	Empty(root);
	flog.close();
}

CarNode* CarBST::Empty(CarNode* root) {
	if (root == NULL)
		return NULL;
	else {
		Empty(root->GetLeft());
		Empty(root->GetRight());
		delete root;
	}
	return NULL;
}

void CarBST::Insert(CarNode* node)
{
	CarNode* tempRoot = nullptr;
	if (root == nullptr)
		root = node;
	else {
		CarNode* ptr = root;
		while (ptr != nullptr) {
			tempRoot = ptr;
			if (node->GetcarNum() < ptr->GetcarNum()) {
				ptr = ptr->GetLeft();
			}
			else {
				ptr = ptr->GetRight();
			}
		}
		if (node->GetcarNum() < tempRoot->GetcarNum())
			tempRoot->SetLeft(node);
		else
			tempRoot->SetRight(node);
	}
}

CarNode* CarBST::Delete(int num)
{
	CarNode* result = remove(root, root, num);
	return nullptr;
}

CarNode* CarBST::remove(CarNode* parent, CarNode* root, int num)
{
	CarNode* temp = nullptr;
	if (root == nullptr) {
		return nullptr;
	}

	if (root->GetcarNum() < num) {
		root->SetRight(remove(root, root->GetRight(), num));
	}
	else if (root->GetcarNum() > num) {
		root->SetLeft(remove(root, root->GetLeft(), num));
	}
	else {
		if (root->GetLeft() && root->GetRight()) {

			temp = findMax(root->GetLeft());
			root->SetcarNum(temp->GetcarNum());
			root->SetcarOwner(temp->GetcarOwner());
			root->Setstate(temp->Getstate());
			root->SetLeft(remove(root, root->GetLeft(), temp->GetcarNum()));
		}
		else {
			temp = (root->GetLeft() == nullptr) ? root->GetRight() : root->GetLeft();
			delete root;
			return temp;
		}
	}

	return root;
}

CarNode* CarBST::Search(int num)
{
	CarNode* result = find(root, num);
	return result;
}

bool CarBST::Print(const char* order)
{
	if (strcmp(order, "R_PRE") == 0) {
		Preorder(root);
		return true;
	}
	else if (strcmp(order, "I_PRE") == 0) {
		iterativePreorder();
		return true;
	}
	else if (strcmp(order, "R_IN") == 0) {
		Inorder(root);
		return true;
	}
	else if (strcmp(order, "I_IN") == 0) {
		iterativeInorder();
		return true;
	}
	else if (strcmp(order, "R_POST") == 0) {
		Postorder(root);
		return true;
	}
	else if (strcmp(order, "I_POST") == 0) {
		iterativePostorder();
		return true;
	}
	else if (strcmp(order, "I_LEVEL") == 0) {
		iterativeInorder();
		return true;
	}
	else {
		return false;
	}
}

bool CarBST::Save()
{
	PreorderSave(root);
	return true;
}

void CarBST::PreorderSave(CarNode* node)
{
	if (node == NULL)
		return;
	
	string filePath = "event_list_car.txt";

	ofstream writeToFile;
	writeToFile.open(filePath, ios::app);

	string tmp = to_string(index) + "\t" + to_string(node->GetcarNum()) + "\t" + node->GetcarOwner() + "\t" + node->Getstate() + "\n";
	writeToFile.write(tmp.c_str(), tmp.size());

	writeToFile.close();

	PreorderSave(node->GetLeft());
	PreorderSave(node->GetRight());
}

void CarBST::Inorder(CarNode* node)
{
	if (node == NULL)
		return;
	Inorder(node->GetLeft());
	cout << node->GetcarNum() << " " << node->GetcarOwner() << " " << node->Getstate() << endl;
	flog << node->GetcarNum() << " " << node->GetcarOwner() << " " << node->Getstate() << endl;
	Inorder(node->GetRight());
}

void CarBST::Preorder(CarNode* node)
{
	if (node == NULL)
		return;
	cout << node->GetcarNum() << " " << node->GetcarOwner() << " " << node->Getstate() << endl;
	flog << node->GetcarNum() << " " << node->GetcarOwner() << " " << node->Getstate() << endl;
	Preorder(node->GetLeft());
	Preorder(node->GetRight());
}

void CarBST::Postorder(CarNode* node)
{
	if (node == NULL)
		return;
	Postorder(node->GetLeft());
	Postorder(node->GetRight());
	cout << node->GetcarNum() << " " << node->GetcarOwner() << " " << node->Getstate() << endl;
	flog << node->GetcarNum() << " " << node->GetcarOwner() << " " << node->Getstate() << endl;
}

void CarBST::levelorder()
{
	if (root == nullptr)
		return;

	queue<CarNode*> q;
	q.push(root);
	
	while (true) { //queue = fifo, root를 빼면서, root->left, root->right 넣음
		if (q.empty()) break;

		CarNode* ptr = q.front();
		q.pop();
		cout << ptr->GetcarNum() << " " << ptr->GetcarOwner() << " " << ptr->Getstate() << endl;
		flog << ptr->GetcarNum() << " " << ptr->GetcarOwner() << " " << ptr->Getstate() << endl;

		if (ptr->GetLeft() != nullptr) q.push(ptr->GetLeft());
		if (ptr->GetRight() != nullptr) q.push(ptr->GetRight());		
	}
}

void CarBST::iterativeInorder()
{
	if (root == nullptr)
		return;

	stack<CarNode*> st;
	CarNode* ptr = root;

	while (true) {	//stack = lifo, left root right
		while (ptr) { // 왼쪽으로 NULL이 나올떄까지 스택에 노드를 저장
			st.push(ptr); 
			ptr = ptr->GetLeft();
		}
		if (st.empty()) break;

		ptr = st.top(); // 가장 마지막에 들어간 노드 가져와서 출력
		st.pop();
		cout << ptr->GetcarNum() << " " << ptr->GetcarOwner() << " " << ptr->Getstate() << endl;
		flog << ptr->GetcarNum() << " " << ptr->GetcarOwner() << " " << ptr->Getstate() << endl;

		ptr = ptr->GetRight(); // 해당 노드의 오른쪽 자식 노드 확인
	}
}

void CarBST::iterativePreorder()
{
	if (root == nullptr)
		return;

	stack<CarNode*> st;
	st.push(root);

	while (true) { //stack = lifo, root left right
		if (st.empty()) break;

		CarNode* ptr = st.top();
		st.pop(); 
		cout << ptr->GetcarNum() << " " << ptr->GetcarOwner() << " " << ptr->Getstate() << endl;
		flog << ptr->GetcarNum() << " " << ptr->GetcarOwner() << " " << ptr->Getstate() << endl;

		if (ptr->GetRight() != nullptr) st.push(ptr->GetRight()); // 스택을 사용하기 때문에 왼쪽부터 출력됨
		if (ptr->GetLeft() != nullptr) st.push(ptr->GetLeft());
	}
}

void CarBST::iterativePostorder()
{
	if (root == nullptr)
		return;

	stack<CarNode*> st1; 
	stack<CarNode*> st2; 
	st1.push(root);

	while (true) { //stack = lifo, left right root
		if (st1.empty()) break;

		CarNode* ptr = st1.top();
		st1.pop();
		st2.push(ptr);

		if (ptr->GetLeft() != nullptr) st1.push(ptr->GetLeft());
		if (ptr->GetRight() != nullptr) st1.push(ptr->GetRight());	
	}

	while (true) {
		if (st2.empty()) break;

		CarNode* ptr = st2.top();
		st2.pop();
		cout << ptr->GetcarNum() << " " << ptr->GetcarOwner() << " " << ptr->Getstate() << endl;
		flog << ptr->GetcarNum() << " " << ptr->GetcarOwner() << " " << ptr->Getstate() << endl;
	}
}

CarNode* CarBST::find(CarNode* node, int num)
{
	if (node == nullptr) return nullptr;

	if (node->GetcarNum() == num) {
		return node;
	}
	else if (node->GetcarNum() > num) {
		return find(node->GetLeft(), num);
	}
	else {
		return find(node->GetRight(), num);
	}
}

CarNode* CarBST::findMin(CarNode* node)
{
	if (node == nullptr)
		return nullptr;
	else if (node->GetLeft() == nullptr)
		return node;
	else
		return findMin(node->GetLeft());
}

CarNode* CarBST::findMax(CarNode* node)
{
	if (node == nullptr)
		return nullptr;
	else if (node->GetRight() == nullptr)
		return node;
	else
		return findMax(node->GetRight());
}
