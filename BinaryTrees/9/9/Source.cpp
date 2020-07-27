#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class Node;
class Tree;

class Node
{
private:
	int value;
	int h;
	int l;
	bool isItInPath;
	Node* left, * right;

public:
	Node() {
		value = h = l = 0;
		left = right = nullptr;
		isItInPath = false;
	}

	Node(int value) {
		this->value = value;
		h = l = 0;
		left = right = nullptr;
		isItInPath = false;
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

	int getH() {
		return h;
	}

	int getL() {
		return l;
	}

	bool isInPath() {
		return isItInPath;
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

	void setH(int h) {
		this->h = h;
	}

	void setL(int l) {
		this->l = l;
	}

	void setInPath(bool isItInPath) {
		this->isItInPath = isItInPath;
	}
};

class Tree {
private:
	Node* root;
	int maxL = 0;

	void preoderTraversalMarkRootsRecursion(Node* curNode) {
		if (curNode != nullptr) {
			(curNode->getL() == maxL) ? curNode->setInPath(true) : curNode->setInPath(false);
			preoderTraversalMarkRootsRecursion(curNode->getLeft());
			preoderTraversalMarkRootsRecursion(curNode->getRight());
		}
	}

	void preorderTraversalMarkPathVerticesRecursion(Node* curNode, bool f) {
		if (curNode != nullptr) {
			if (curNode->isInPath()) {
				f = true;
				preorderTraversalMarkPathVerticesRecursion(curNode->getLeft(), f);
				preorderTraversalMarkPathVerticesRecursion(curNode->getRight(), f);
			}
			else {
				if (curNode->getLeft() != nullptr && curNode->getRight() != nullptr) {
					if (curNode->getLeft()->getH() >= curNode->getRight()->getH()) {
						preorderTraversalMarkPathVerticesRecursion(curNode->getLeft(), f);
					}
					if (curNode->getLeft()->getH() <= curNode->getRight()->getH())
					{
						preorderTraversalMarkPathVerticesRecursion(curNode->getRight(), f);
					}
				} else {
					preorderTraversalMarkPathVerticesRecursion(curNode->getLeft(), f);
					preorderTraversalMarkPathVerticesRecursion(curNode->getRight(), f);
				}
			}
			curNode->setInPath(f);
		}
	}

	void preoderTraversalPrintRecursion(ofstream& fout, Node* curNode) {
		if (curNode != nullptr) {
			fout << curNode->getValue() << endl;
			preoderTraversalPrintRecursion(fout, curNode->getLeft());
			preoderTraversalPrintRecursion(fout, curNode->getRight());
		}
	}

	void inorderTraversalDelete2VertexRecursion(Node* curNode, int& count) {
		if (curNode != nullptr) {
			inorderTraversalDelete2VertexRecursion(curNode->getLeft(), count);
			if (curNode->isInPath()) {
				count++;
				if (count == 2) {
					deleteKey(curNode->getValue());
				}
			}
			inorderTraversalDelete2VertexRecursion(curNode->getRight(), count);
		}
	}

	void postorderTraversalCountHLRecursion(Node* curNode) {
		if (curNode != nullptr) {
			postorderTraversalCountHLRecursion(curNode->getLeft());
			postorderTraversalCountHLRecursion(curNode->getRight());
			int h = 0;
			int l = 0;
			bool hasChild = false;
			if (curNode->getLeft() != nullptr) {
				h += curNode->getLeft()->getH();
				l += curNode->getLeft()->getH() + 1;
				hasChild = true;
			}
			if (curNode->getRight() != nullptr) {
				h = max(curNode->getRight()->getH(), h);
				l += curNode->getRight()->getH() + 1;
				hasChild = true;
			}
			h = hasChild ? h + 1 : h;
			curNode->setH(h);
			curNode->setL(l);
			maxL = max(l, maxL);
		}
	}

public:
	Tree() {
		root = nullptr;
	}

	int getMaxL() {
		return maxL;
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

	Node* searchParent(Node* curNode) {
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

	void preoderTraversalMarkRoots() {
		preoderTraversalMarkRootsRecursion(root);
	}

	void preorderTraversalMarkPathVertices() {
		bool f = false;
		preorderTraversalMarkPathVerticesRecursion(root, f);
	}
	void inorderTraversalDelete2Vertex() {
		int count = 0;
		inorderTraversalDelete2VertexRecursion(root, count);
	}

	void postorderTraversalCountHL() {
		postorderTraversalCountHLRecursion(root);
	}

	void preoderTraversalPrint(ofstream& fout) {
		preoderTraversalPrintRecursion(fout, root);
	}
};

int main() {
	ifstream fin("in.txt");
	ofstream fout("out.txt");
	Tree* tree = new Tree();
	while (!fin.eof())
	{
		int value;
		fin >> value;
		tree->add(value);
	}

	tree->postorderTraversalCountHL();
	tree->preoderTraversalMarkRoots();
	tree->preorderTraversalMarkPathVertices();
	tree->inorderTraversalDelete2Vertex();
	tree->preoderTraversalPrint(fout);
	return 0;
}