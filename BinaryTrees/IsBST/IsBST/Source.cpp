#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Node;

class Node
{
private:
	long value;
	Node* left, * right;

public:
	Node() {
		value = 0;
		left = right = nullptr;
	}

	Node(long value) {
		this->value = value;
		left = right = nullptr;
	}

	long getValue() {
		return value;
	}

	Node* getLeft() {
		return left;
	}

	Node* getRight() {
		return right;
	}

	void setValue(long value) {
		this->value = value;
	}

	void setLeft(Node* left) {
		this->left = left;
	}

	void setRight(Node* right) {
		this->right = right;
	}
};

int main() {
	ifstream fin("bst.in");
	ofstream fout("bst.out");
	int n, value;
	fin >> n;
	vector<Node*> parents(n);
	fin >> value;
	parents[0] = new Node(value);

	bool isBST = true;
	long p;
	char c;
	bool f1 = true;
	bool f2 = false;

	for (int i = 1; (i < n) && (f1 | f2); i++)
	{
		fin >> value >> p >> c;
		parents[i] = new Node(value);
		Node* pa = parents[p - 1];
		f1 = false;
		f2 = false;
		if ((value < pa->getValue()) && (pa->getLeft() == nullptr) && (c == 'L')) {
			pa->setLeft(parents[i]);
			f1 = true;
		}
		if ((value >= pa->getValue()) && (pa->getRight() == nullptr) && (c == 'R')) {
			pa->setRight(parents[i]);
			f2 = true;
		}
	}

	if (f1 | f2) {
		fout << "YES";
	}
	else {
		fout << "NO";
	}
	return 0;
}

