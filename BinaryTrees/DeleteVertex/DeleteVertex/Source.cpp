#include <iostream>
#include <fstream>
#include <string>

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

	Node* searchParent(Node *curNode) {
		Node* temp = root;
		Node* prevNode = nullptr;

		while (temp != nullptr && temp != curNode) {
			prevNode = temp;
			if (curNode->getValue() < temp->getValue()) {
				temp = temp->getLeft();
			}
			else {
				temp = temp->getRight();
			}
		}
		return prevNode;
	}

	Node* searchRecursion(Node* curNode, int value) {
		if (curNode == nullptr || curNode->getValue() == value) {
			return curNode;
		}
		if (value < curNode->getValue()) {
			return searchRecursion(curNode->getLeft(), value);
		}
		else {
			return searchRecursion(curNode->getRight(), value);
		}
	}

	bool search(int value) {
		return (searchRecursion(root, value) != nullptr);
	}


	void deleteKey(int value) {
 		Node* delNode = searchRecursion(root, value);

		if (delNode == nullptr) {
			return;
		}

		Node* parentDelNode = searchParent(delNode);

		if (delNode->getLeft() == nullptr && delNode->getRight() == nullptr) {
			if (parentDelNode == nullptr) {
				root = nullptr;
			}
			else {
				if (parentDelNode->getLeft() == delNode) {
					parentDelNode->setLeft(nullptr);
				}
				else {
					parentDelNode->setRight(nullptr);
				}
			}
		}
		else if (delNode->getLeft() == nullptr || delNode->getRight() == nullptr) {
			if (parentDelNode == nullptr) {
				if (delNode->getLeft() == nullptr) {
					root = delNode->getRight();
				}
				else {
					root = delNode->getLeft();
				}
			}
			else if (delNode->getLeft() == nullptr) {
				if (parentDelNode->getLeft() == delNode) {
					parentDelNode->setLeft(delNode->getRight());
				}
				else {
					parentDelNode->setRight(delNode->getRight());
				}
			}
			else {
				if (parentDelNode->getLeft() == delNode) {
					parentDelNode->setLeft(delNode->getLeft());
				}
				else {
					parentDelNode->setRight(delNode->getLeft());
				}
			}
		}
		else {
			Node* nextNode = delNode->getRight();
			while (nextNode->getLeft() != nullptr) {
				nextNode = nextNode->getLeft();
			}
			Node* parentNextNode = searchParent(nextNode);
			delNode->setValue(nextNode->getValue());
			if (parentNextNode != delNode) {
				parentNextNode->setLeft(nextNode->getRight());
			}
			else {
				parentNextNode->setRight(nextNode->getRight());
			}
		}
	}
};

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	Tree *tree = new Tree();
	int deleteKey;
	fin >> deleteKey;
	string line;
	getline(fin, line);
	while (!fin.eof())
	{
		int value;
		fin >> value;
		tree->add(value);
	}
	
	tree->deleteKey(deleteKey);
	tree->preoderTraversal(fout);
	return 0;
}

