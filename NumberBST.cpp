#include "NumberBST.h"
#include <queue>
#include <stack>
#include <fstream>

NumberBST::NumberBST()
{
	root = nullptr;
	nodeCnt = 0; //Numbernode의 개수
	totalList = 0; //모든 NumberNode의 carNode 개수
	currentNode = 0; //BST index
	flog.open("log.txt", ios::app);
}


NumberBST::~NumberBST()
{
	root = Empty(root);
	flog.close();
}
NumberNode* NumberBST::Empty(NumberNode* root) {
	if (root == NULL)
		return NULL;
	else {
		Empty(root->GetLeft());
		Empty(root->GetRight());
		delete root;
	}
	return NULL;
}

void NumberBST::Insert(NumberNode* node)
{
	NumberNode* tempRoot = nullptr;
	if (root == nullptr)
		root = node;
	else {
		NumberNode* ptr = root;
		while (ptr != nullptr) { //크기 비교해서 빈자리에 넣음
			tempRoot = ptr;
			if (node->GetNumber() < ptr->GetNumber()) {
				ptr = ptr->GetLeft();
			}
			else {
				ptr = ptr->GetRight();
			}
		}
		if (node->GetNumber() < tempRoot->GetNumber())
			tempRoot->SetLeft(node);
		else
			tempRoot->SetRight(node);
		nodeCnt++;
	}
}

NumberNode* NumberBST::Delete(int num)
{
	NumberNode* result = remove(root, root, num);
	return result;
}

NumberNode* NumberBST::Search(int num)
{
	NumberNode* result = find(root, num);
	return result;
}


void NumberBST::Preorder(NumberNode* node) //root left right 
{
	if (node == NULL)
		return;
	cout << node->GetNumber() << " ";
	flog << node->GetNumber() << " ";
	Preorder(node->GetLeft());
	Preorder(node->GetRight());

}
void NumberBST::Postorder(NumberNode* node) //left right root
{
	if (node == NULL)
		return;
	Postorder(node->GetLeft());
	Postorder(node->GetRight());
	cout << node->GetNumber() << " ";
	flog << node->GetNumber() << " ";
}
void NumberBST::Inorder(NumberNode* node) //left root right
{
	if (node == NULL)
		return;
	Inorder(node->GetLeft());
	cout << node->GetNumber() << " ";      
	flog << node->GetNumber() << " ";
	Inorder(node->GetRight());

}
NumberNode* NumberBST::remove(NumberNode* parent, NumberNode* root, int num)
{
	NumberNode* temp = nullptr;
	if (root == nullptr) {
		return nullptr;
	}

	if (root->GetNumber() < num) {
		root->SetRight(remove(root, root->GetRight(), num));
	}
	else if (root->GetNumber() > num) {
		root->SetLeft(remove(root, root->GetLeft(), num));
	}
	else {
		if (root->GetLeft() && root->GetRight()) {

			temp = findMax(root->GetLeft());
			root->SetNumber(temp->GetNumber());
			root->SetLeft(remove(root, root->GetLeft(), temp->GetNumber()));
		}
		else {
			temp = (root->GetLeft() == nullptr) ? root->GetRight() : root->GetLeft();
			delete root;
			return temp;
		}
	}

	return root;
}
bool NumberBST::Print(char* BST)
{
	if (root == nullptr)
		return false;
	
	stack<NumberNode*> st;
	st.push(root);

	while(true) {
		if (st.empty()) break;

		NumberNode* ptr = st.top();
		st.pop();
		ptr->GetBST()->Print(BST);

		if (ptr->GetRight() != nullptr) st.push(ptr->GetRight());
		if (ptr->GetLeft() != nullptr) st.push(ptr->GetLeft());		
	}

	return true;
}
bool NumberBST::Save()
{
	PreorderSave(root);
	return true;
}
void NumberBST::PreorderSave(NumberNode* node)
{
	if (node == NULL)
		return;
	node->GetBST()->Save();
	Preorder(node->GetLeft());
	Preorder(node->GetRight());
}
NumberNode* NumberBST::find(NumberNode* node, int num)
{
	if (node == nullptr) return nullptr;

	if (node->GetNumber() == num) {
		return node;
	}
	else if (node->GetNumber() > num) {
		return find(node->GetLeft(), num);
	}
	else {	
		return find(node->GetRight(), num);
	}
}
NumberNode* NumberBST::findMin(NumberNode* node)
{
	if (node == nullptr)
		return nullptr;
	else if (node->GetLeft() == nullptr)
		return node;
	else
		return findMin(node->GetLeft());
}

NumberNode* NumberBST::findMax(NumberNode* node)
{
	if (node == nullptr)
		return nullptr;
	else if (node->GetRight() == nullptr)
		return node;
	else
		return findMax(node->GetRight());
}

int NumberBST::getCnt()
{
	return nodeCnt;
}

void NumberBST::setCnt(int cnt)
{
	this->nodeCnt = cnt;
}
