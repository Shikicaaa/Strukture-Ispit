#pragma once

#include "BSTNodeInt.h"

class BSTreeInt
{
protected:
	BSTNodeInt* root;
	long numOfElements;

	void deleteTree(BSTNodeInt* ptr);

	void inorder(const BSTNodeInt* ptr) const;
	void preorder(const BSTNodeInt* ptr) const;
	void postorder(const BSTNodeInt* ptr) const;

	int getDepth(const BSTNodeInt* ptr);
	int countLeaves(const BSTNodeInt* ptr);
	int getMoment(const BSTNodeInt* ptr);
	void balance(int* data, int first, int last);
	int maxHeightDiff(BSTNodeInt* node, BSTNodeInt** maxNode, int& maxVal);
	void traversal(const BSTNodeInt* ptr,int* data, int i);
public:
	BSTNodeInt* maxHeightDiff();
	BSTreeInt() { root = nullptr; numOfElements = 0; }
	~BSTreeInt() { deleteTree(root); }

	bool isEmpty() const { return root == nullptr; }

	bool isInTree(int el) const { return search(el) != nullptr; }
	BSTNodeInt* search(int el) const;

	void insert(int el);
	void deleteByCopying(int el);
	void deleteByMerging(int el);

	void preorder() const { preorder(root); }
	void inorder() const { inorder(root); }
	void postorder() const { postorder(root); }

	void iterativePreorder() const;
	void breadthFirstSearch() const;
	int getDepth() { return getDepth(root); }
	int getHeight() { return 1 + getDepth(); }
	int countLeaves() { return countLeaves(root); }
	int getWeight() { return countLeaves(root); }
	int getMoment() { return getMoment(root); }
	void balance() { 
		int n = getMoment();
		int* data = new int[n];
		int i = 0;
		while (root)
		{
			data[i++] = root->getKey();
			deleteByCopying(root->key);
		}
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n - 1; j++) {
				if (data[j] > data[i]) {
					int temp = data[j];
					data[j] = data[i];
					data[i] = temp;
				}
			}
		}
		balance(data, 0, n-1);
		delete[] data;
	}
};

