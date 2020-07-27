#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

#define int long long
#define Integer Long

class Node;
class Tree;

struct Integer
{
	mutable int value;
	
	Integer(int value) {
		this->value = value;
	}

	
	bool operator < (const Integer& longlong) const {
		return value < longlong.value;
	}
	
};

class Node
{
private:
	int value;
	int h;
	int l;
	int rootLength;
	bool isItRoot;
	bool isItRightVertex;
	Node* left, * right, * parent;
	set<Integer> pathLeft;
	set<Integer> pathRight;
	set<Integer> pathParent;

public:
	Node() {
		value = h = l = rootLength = 0;
		left = right = parent = nullptr;
		isItRoot = false;
		isItRightVertex = false;
	}

	Node(int value) {
		this->value = value;
		h = l = rootLength = 0;
		left = right = parent = nullptr;
		isItRoot = false;
		isItRightVertex = false;
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

	Node* getParent() {
		return parent;
	}

	int getH() {
		return h;
	}

	int getL() {
		return l;
	}

	int getRootLength() {
		return rootLength;
	}

	set<Integer> getPathLeft() {
		return pathLeft;
	}

	set<Integer> getPathRight() {
		return pathRight;
	}

	set<Integer> getPathParent() {
		return pathParent;
	}

	bool isRoot() {
		return isItRoot;
	}

	bool isRightVertex() {
		return isItRightVertex;
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

	void setParent(Node* parent) {
		this->parent = parent;
	}

	void setH(int h) {
		this->h = h;
	}

	void setL(int l) {
		this->l = l;
	}

	void setRootLength(int rootLength) {
		this->rootLength = rootLength;
	}

	void setRoot(bool isItRoot) {
		this->isItRoot = isItRoot;
	}

	void setRightVertex(bool isItRightVertex) {
		this->isItRightVertex = isItRightVertex;
	}

	void setPathLeft(set<Integer> pathLeft) {
		this->pathLeft = pathLeft;
	}

	void setPathRight(set<Integer> pathRight) {
		this->pathRight = pathRight;
	}

	void setPathParent(set<Integer> pathParent) {
		this->pathParent = pathParent;
	}

	void addValueToPathLeft(int v) {
		pathLeft.insert(Integer(v));
	}

	void addValueToPathRight(int v) {
		pathRight.insert(Integer(v));
	}

	void addValueToPathParent(int v) {
		pathParent.insert(Integer(v));
	}

	void addSetToPathLeft(set<Integer> set) {
		this->pathLeft.insert(set.begin(), set.end());
	}

	void addSetToPathRight(set<Integer> set) {
		this->pathRight.insert(set.begin(), set.end());
	}

	void addSetToPathParent(set<Integer> set) {
		this->pathParent.insert(set.begin(), set.end());
	}

	void incPathLeft() {
		for (set<Integer>::iterator it = pathLeft.begin(); it != pathLeft.end(); it++) {
			(*it).value++;
		}
	}

	void incPathRight() {
		for (set<Integer>::iterator it = pathRight.begin(); it != pathRight.end(); it++) {
			(*it).value++;
		}
	}

	void incPathParent() {
		for (set<Integer>::iterator it = pathParent.begin(); it != pathParent.end(); it++) {
			(*it).value++;
		}
	}
};

class Tree {
private:
	Node* root;
	int k;
	int maxL = 0;

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

	void preoderTraversalMarkRootsRecursion(Node* curNode) {
		if (curNode != nullptr) {
			if (curNode->getL() == maxL) {
				curNode->setRoot(true);
			}
			else {
				curNode->setRoot(false);
			}
			preoderTraversalMarkRootsRecursion(curNode->getLeft());
			preoderTraversalMarkRootsRecursion(curNode->getRight());
		}
	}

	void postorderTraversalCreatePathLRRecursion(Node* curNode) {
		if (curNode != nullptr) {
			postorderTraversalCreatePathLRRecursion(curNode->getLeft());
			postorderTraversalCreatePathLRRecursion(curNode->getRight());
			
			if (curNode->getLeft() != nullptr) {
				curNode->setPathLeft(curNode->getLeft()->getPathLeft());
				curNode->addSetToPathLeft(curNode->getLeft()->getPathRight());
				curNode->incPathLeft();
			}
			if (curNode->getRight() != nullptr) {
				curNode->setPathRight(curNode->getRight()->getPathLeft());
				curNode->addSetToPathRight(curNode->getRight()->getPathRight());
				curNode->incPathRight();
			}
			if (curNode->getLeft() == nullptr && curNode->getRight() == nullptr) {
				curNode->addValueToPathLeft(0);
				curNode->addValueToPathRight(0);
			}
		}
	}

	void preorderTraversalCreatePathPRecursion(Node* curNode) {
		if (curNode != nullptr) {
			if (curNode->getParent() != nullptr) {
				if (curNode == curNode->getParent()->getLeft()) {
					curNode->setPathParent(curNode->getParent()->getPathParent());
					curNode->addSetToPathParent(curNode->getParent()->getPathRight());
					curNode->incPathParent();
				}
				else {
					curNode->setPathParent(curNode->getParent()->getPathParent());
					curNode->addSetToPathParent(curNode->getParent()->getPathLeft());
					curNode->incPathParent();
				}
			}
			//else if (curNode->getLeft() == nullptr || curNode->getRight() == nullptr) {
			//		curNode->addValueToPathParent(0);
			//	}

			preorderTraversalCreatePathPRecursion(curNode->getLeft());
			preorderTraversalCreatePathPRecursion(curNode->getRight());
		}
	}

	bool hasPathK(set<Integer> setA, set<Integer> setB) {
		if (!setB.empty()) {
			for (Integer length : setB) {
				if (length.value >= k) {
					return true;
				}
			}
		}
		if (!setA.empty()) {
			for (Integer length : setA) {
				if (length.value >= k) {
					return true;
				}
			}
		}
		if (!setA.empty() && !setB.empty()) {
			set<Integer>::iterator l = setA.begin();
			set<Integer>::iterator r = setB.end();
			r--;
			while (l != setA.end() && r != --setB.begin()) {
				int sum = (*l).value + (*r).value;
				if (sum == k) {
					return true;
				}
				else if (sum < k) {
					l++;
				}
				else {
					r--;
				}
			}
		}
		return false;
	}

	void preorderTraversalCheckPathEqualityKRecursion(Node* curNode) {
		if (curNode != nullptr) {
			bool lr = hasPathK(curNode->getPathLeft(), curNode->getPathRight());
			bool lp = hasPathK(curNode->getPathLeft(), curNode->getPathParent());
			bool rp = hasPathK(curNode->getPathParent(), curNode->getPathRight());
			if (!(lr || lp || rp) && (curNode->getRootLength() < k)) {
				curNode->setRightVertex(true);
			}
			preorderTraversalCheckPathEqualityKRecursion(curNode->getLeft());
			preorderTraversalCheckPathEqualityKRecursion(curNode->getRight());
		}
	}

	void inorderTraversalDeleteMaxVertexRecursion(Node* curNode, bool& notDeleted) {
		if (curNode != nullptr) {
			inorderTraversalDeleteMaxVertexRecursion(curNode->getRight(), notDeleted);
			if (curNode->isRightVertex() && notDeleted) {
				deleteKey(curNode->getValue());
				notDeleted = false;
				return;
			}
			inorderTraversalDeleteMaxVertexRecursion(curNode->getLeft(), notDeleted);
		}
	}

	void preoderTraversalPrintRecursion(ofstream& fout, Node* curNode) {
		if (curNode != nullptr) {
			fout << curNode->getValue() << endl;
			preoderTraversalPrintRecursion(fout, curNode->getLeft());
			preoderTraversalPrintRecursion(fout, curNode->getRight());
		}
	}

public:
	Tree(int k) {
		root = nullptr;
		this->k = k;
	}

	void add(int value) {
		if (root == nullptr) {
			root = new Node(value);
			root->setRootLength(0);
		}
		else {
			Node* parent = root;
			Node* temp = root;
			int rootLength = 0;
			while (temp != nullptr) {
				parent = temp;
				if (value < temp->getValue()) {
					temp = temp->getLeft();
					rootLength++;
				}
				else if (value > temp->getValue()) {
					temp = temp->getRight();
					rootLength++;
				}
				else {
					temp = nullptr;
				}
			}
			if (value < parent->getValue()) {
				Node* insertNode = new Node(value);
				insertNode->setRootLength(rootLength);
				insertNode->setParent(parent);
				parent->setLeft(insertNode);
			}
			else if (value > parent->getValue()) {
				Node* insertNode = new Node(value);
				insertNode->setRootLength(rootLength);
				insertNode->setParent(parent);
				parent->setRight(insertNode);
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

	void postorderTraversalCountHL() {
		postorderTraversalCountHLRecursion(root);
	}

	void preorderTraversalMarkRoots() {
		preoderTraversalMarkRootsRecursion(root);
	}

	void postorderTraversalCreatePathLR() {
		postorderTraversalCreatePathLRRecursion(root);
	}

	void preorderTraversalCreatePathP() {
		preorderTraversalCreatePathPRecursion(root);
	}

	void preorderTraversalCheckPathEqualityK() {
		preorderTraversalCheckPathEqualityKRecursion(root);
	}

	void inorderTraversalDeleteMaxVertex() {
		bool notDeleted = true;
		inorderTraversalDeleteMaxVertexRecursion(root, notDeleted);
	}

	void preoderTraversalPrint(ofstream& fout) {
		if (root != nullptr) {
			preoderTraversalPrintRecursion(fout, root);
		}
		else {
			fout << "No tree" << endl;
		}
	}
};

void main() {
	ifstream fin("tst.in");
	ofstream fout("tst.out");
	int k;
	fin >> k;
	int count = 0;
	Tree* tree = new Tree(k);
	while (!fin.eof())
	{
		int value;
		fin >> value;
		tree->add(value);
		count++;
	}

	if (k == 0 && count == 1) {
		fout << "No tree" << endl;
	}
	else {
		tree->postorderTraversalCountHL();
		tree->preorderTraversalMarkRoots();
		tree->postorderTraversalCreatePathLR();
		tree->preorderTraversalCreatePathP();
		tree->preorderTraversalCheckPathEqualityK();
		tree->inorderTraversalDeleteMaxVertex();
		tree->preoderTraversalPrint(fout);
	}
}