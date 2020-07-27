#include <iostream>
#include <fstream>

using namespace std;

class Node;
class Tree;

class Node
{
private:
	int value;
	Node* left, *right;

public:
	Node() {
		value = 0;
		left = right = nullptr;
	}

	Node(int value) {
		this->value = value;
		left = right = nullptr;
	}

	int getValue() {
		return value;
	}

	Node* getLeft() {
		return left;
	}

	Node* getRight() {
		return right;
	}

	void setValue(int value) {
		this->value = value;
	}

	void setLeft(Node* left) {
		this->left = left;
	}

	void setRight(Node* right) {
		this->right = right;
	}
};

class Tree {
private:
	Node* root;

	void preorderTraversalRecursion(ofstream& fout, Node *curNode) {
		if (curNode != nullptr) {
			fout << curNode->getValue() << endl;
			preorderTraversalRecursion(fout, curNode->getLeft());
			preorderTraversalRecursion(fout, curNode->getRight());
		}
	}

public:
	Tree() {
		root = nullptr;
	}

	void add(int value) {
		if (root == nullptr) {
			root = new Node(value);
		}
		else {
			Node* parent = root;
			Node* temp = root;
			while (temp != nullptr) {
				parent = temp;
				if (value < temp->getValue()) {
					temp = temp->getLeft();
				}
				else if (value > temp->getValue()) {
					temp = temp->getRight();
				}
				else {
					temp = nullptr;
				}
			}
			if (value < parent->getValue()) {
				parent->setLeft(new Node(value));
			}
			else if (value > parent->getValue()) {
				parent->setRight(new Node(value));
			}
		}
	}

	void preoderTraversal(ofstream& fout) {
		preorderTraversalRecursion(fout, root);
	}
};

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	Tree *tree = new Tree();
	while (!fin.eof())
	{
		int value;
		fin >> value;
		tree->add(value);
	}
	
	tree->preoderTraversal(fout);
	return 0;
}

