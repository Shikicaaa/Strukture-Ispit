#include "BSTreeInt.h"

#include <exception>
using namespace std;

#include "QueueAsArrayInt.h"
#include "StackAsArrayInt.h"
#include "BSTNodeInt.h"
#include <time.h>



/*
	DECEMBAR 2023
	DECEMBAR 2023
	DECEMBAR 2023
*/
BSTNodeInt* BSTreeInt::maxHeightDiff() {
	return null;
}
int BSTreeInt::countNodes() {
	int broj = 0;
	return countNodes(root, broj);
}
int BSTreeInt::countNodes(const BSTNodeInt* ptr,int& broj) {
	if (ptr == NULL) return 0;
	ptr->domace > ptr->gosti ? broj++ : broj = broj;
	return countNodes(ptr->left, broj) + countNodes(ptr->right, broj);
}
/*
	JANUAR 2024
	JANUAR 2024
	JANUAR 2024
*/
int BSTreeInt::countCloseParents(BSTNodeInt* ptr, int n) { 
	if (ptr == NULL) {
		return 0;
	}
	int count = 0;
	if (ptr->right != NULL && ptr->left != NULL) {
		if (abs(ptr->key - ptr->right->key) < n && abs(ptr->key - ptr->left->key) < n) count = 1;
	}
	count += countCloseParents(ptr->right, n);
	count += countCloseParents(ptr->left, n);
	return count;
}
int BSTreeInt::countCloseParents(int n) {
	return countCloseParents(root, n);
}

/*	JUNSKI 2023
	JUNSKI 2023
	JUNSKI 2023
*/
bool BSTreeInt::nodeInRange(const BSTNodeInt* ptr, int min, int max) {
	if (ptr == NULL) return false;
	if (ptr->key > min && ptr->key < max) return true;
	return nodeInRange(ptr->left, min, max) || nodeInRange(ptr->right, min, max);
}
int BSTreeInt::countSmaller(const BSTNodeInt* root, int d)
{
	if (root == NULL) {
		return 0;
	}
	int count = 0;
	if (nodeInRange(root, root->key - d, root->key) || nodeInRange(root, root->key - d, root->key)) {
		count = 1;
	}
	count += countSmaller(root->left, d);
	count += countSmaller(root->right, d);
	return count;
}
int BSTreeInt::countSmaller(int d) {
	return countSmaller(root, d);
}

void BSTreeInt::deleteTree(BSTNodeInt* ptr)
{
	if (ptr != nullptr) {
		deleteTree(ptr->left);
		deleteTree(ptr->right);
		delete ptr;
	}
}
/*
	KOLOKVIJUM 2 2023 A
	KOLOKVIJUM 2 2023 A
	KOLOKVIJUM 2 2023 A
*/
BSTNodeInt * BSTreeInt::maxAbsBetweenSubtrees()
{
	BSTNodeInt* maxAbsNode = nullptr;
	int maxAbsValue = 0;
	maxAbs(root, maxAbsValue, &maxAbsNode);
	return maxAbsNode;
}

int BSTreeInt::maxAbs(BSTNodeInt* node, int& maxAbsValue, BSTNodeInt** maxAbsNode)
{
	if (node == nullptr)
		return 0;

	// ako je list uracunaj ga
	if (node->left == nullptr && node->right == nullptr)
		return 1;


	int left = maxAbs(node->left, maxAbsValue, maxAbsNode);
	int right = maxAbs(node->right, maxAbsValue, maxAbsNode);

	cout << "Cvor: " << node->getKey() << " -> razlika: " << abs(left - right) << endl;

	if (abs(right - left) > maxAbsValue && node != root) {
		maxAbsValue = abs(right - left);
		*maxAbsNode = node;
	}

	return left + right + 1;
}

/*
	KOLOKVIJUM 2 2023 B
	KOLOKVIJUM 2 2023 B
*/
BSTNodeInt* BSTreeInt::razlikaSume() {
	int razlika = 0;//prvi je 0ti element i 0 je parna
	BSTNodeInt* node = NULL;
	razlikaSumeParnihNeparnih(root,razlika, &node);
	return node;
}
int BSTreeInt::razlikaSumeParnihNeparnih(BSTNodeInt* node, int &razlika, BSTNodeInt** maxNode) {
	if (node == NULL) return 0;
	if (node->left == nullptr && node->right == nullptr) return 1;
	int sumap = razlikaSumeParnihNeparnih(node->left, razlika, maxNode);
	int sumanp = razlikaSumeParnihNeparnih(node->right, razlika, maxNode);

	int currentsum = node->key % 2 == 0 ? sumap + 1 : sumanp + 1;
	int othersum = node->key % 2 == 0 ? sumanp : sumap;

	std::cout << "Razlika parnih i neparnih <" << node->getKey() << ">:" << abs(sumap - sumanp) << endl;
	if (abs(currentsum - othersum) > razlika) {
		razlika = abs(currentsum - othersum);
		*maxNode = node;
	}
	return othersum + currentsum;
}
BSTNodeInt* BSTreeInt::search(int el) const
{
	BSTNodeInt* ptr = root;
	while (ptr != nullptr)
		if (ptr->isEQ(el))
			return ptr;
		else if (ptr->isGT(el))
			ptr = ptr->left;
		else
			ptr = ptr->right;
	return nullptr;
}

void BSTreeInt::insert(int el)
{
	BSTNodeInt* ptr = root, * par = nullptr;
	while (ptr != nullptr) {  // trazenje mesta za umetanje novog cvora
		par = ptr;
		if (ptr->isLT(el))
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}
	if (root == nullptr)    // stablo je prazno
	{
		root = new BSTNodeInt(el);
		root->domace = rand() % 100 + 1;
		root->gosti = rand() % 100 + 1;
	}
	else if (par->isLT(el)) {
		time(0);
		par->right = new BSTNodeInt(el);
		par->domace = rand() % 100 + 1;
		par->gosti = rand() % 100 + 1;
	}
	else {
		time(new time_t(10));
		par->left = new BSTNodeInt(el);
		par->domace = rand() % 100 + 1;
		par->gosti = rand() % 100 + 1;

	}
	numOfElements++;
}

void BSTreeInt::deleteByCopying(int el)
{
	BSTNodeInt* node, * ptr = root, * par = nullptr;
	while (ptr != nullptr && !ptr->isEQ(el)) { 	// nalazenje cvora sa zeljenim el.
		par = ptr;
		if (ptr->isLT(el)) ptr = ptr->right;
		else ptr = ptr->left;
	}
	node = ptr;
	if (ptr != nullptr && ptr->isEQ(el)) {
		if (node->right == nullptr)             // cvor nema desnog potomka (1)
			node = node->left;
		else if (node->left == nullptr)         // cvor nema levog potomka (2)
			node = node->right;
		else {									// cvor ima oba potomka (3)
			BSTNodeInt* tmp = node->left;
			BSTNodeInt* parent = node;
			while (tmp->right != nullptr) {		// nalazenje krajnjeg desnog cvora
				parent = tmp;             		// u levom podstablu
				tmp = tmp->right;
			}
			node->setKey(tmp->getKey());		// prepisivanje reference na kljuc 
			if (parent == node)           		// tmp je direktni levi potomak node-a
				parent->left = tmp->left;		// ostaje isti raspored u levom podstablu
			else
				parent->right = tmp->left; 		// levi potomak tmp-a 
			delete tmp;							// se pomera na mesto tmp-a
			numOfElements--;
			return;
		}
		if (ptr == root)						// u slucaju (1) i (2) samo je pomerena
			root = node;						// referenca node pa je potrebno
		else if (par->left == ptr)				// izmeniti i link prethodnog cvora
			par->left = node;					// u slucaju (3) ovo nema dejstva
		else
			par->right = node;
		delete ptr;
		numOfElements--;
	}
	else if (root != nullptr)
		throw new exception("Element is not in the tree!");
	else
		throw new exception("The tree is empty!");
}

void BSTreeInt::deleteByMerging(int el)
{
	BSTNodeInt* node, * ptr = root, * par = nullptr;
	while (ptr != nullptr && !ptr->isEQ(el)) {	// nalazenje cvora sa zeljenim el.
		par = ptr;
		if (ptr->isLT(el)) ptr = ptr->right;
		else ptr = ptr->left;
	}
	node = ptr;
	if (ptr != nullptr && ptr->isEQ(el)) {
		if (node->right == nullptr)				// cvor nema desnog potomka (1)
			node = node->left;
		else if (node->left == nullptr)			// cvor nema levog potomka (2)
			node = node->right;
		else {									// cvor ima oba potomka (3)
			BSTNodeInt* tmp = node->left;		// uvek ide levi !!!!!!!!!!!!!!!!!!!!
			while (tmp->right != nullptr)		// nalazenje krajnjeg desnog cvora
				tmp = tmp->right;				// u levom podstablu
			tmp->right = node->right;			// prebacivanje desnog linka node-a u tmp
			node = node->left;					// na tekucem mestu bice prvi levi potomak
		}
		if (ptr == root)
			root = node;
		else if (par->left == ptr)
			par->left = node;
		else
			par->right = node;
		delete ptr;
		numOfElements--;
	}
	else if (root != nullptr)
		throw new exception("Element is not in the tree!");
	else
		throw new exception("The tree is empty!");
}

void BSTreeInt::preorder(const BSTNodeInt* ptr) const
{
	if (ptr != nullptr) {
		ptr->visit();
		std::cout << "Levo: ";
		preorder(ptr->left);
		std::cout << "Desno: ";
		preorder(ptr->right);
		std::cout << "\n";
	}
}

void BSTreeInt::inorder(const BSTNodeInt* ptr) const
{
	if (ptr != nullptr) {
		inorder(ptr->left);
		ptr->visit();
		inorder(ptr->right);
	}
}

void BSTreeInt::postorder(const BSTNodeInt* ptr) const
{
	if (ptr != nullptr) {
		postorder(ptr->left);
		postorder(ptr->right);
		ptr->visit();
	}
}

int BSTreeInt::getDepth(const BSTNodeInt* ptr)
{
	if (ptr == NULL)
		return -1;
	int lc = getDepth(ptr->left);
	int rc = getDepth(ptr->right);
	return 1 + (lc > rc ? lc : rc);
}
int BSTreeInt::countLeaves(const BSTNodeInt* ptr)
{
	if (ptr == NULL)
		return 0;
	if (ptr->right != NULL || ptr->left != NULL)
		return countLeaves(ptr->right) + countLeaves(ptr->left);
	if (ptr->right == NULL && ptr->left == NULL)
		return 1;


}
int BSTreeInt::getMoment(const BSTNodeInt* ptr) {
	if (ptr == nullptr)
		return 0;
	if (ptr->left == NULL && ptr->right == NULL)
		return 1;
	return 1 + getMoment(ptr->left) + getMoment(ptr->right);
}
void BSTreeInt::iterativePreorder() const
{
	BSTNodeInt* ptr = root;
	StackAsArrayBSTNodeInt stack(numOfElements);
	if (ptr != nullptr) {
		stack.push(ptr);
		while (!stack.isEmpty()) {
			ptr = stack.pop();
			ptr->visit();
			if (ptr->right != nullptr)	// levi potomak se stavlja u magacin
				stack.push(ptr->right); // posle desnog, da bi se prvi obradio
			if (ptr->left != nullptr)
				stack.push(ptr->left);
		}
	}
}

void BSTreeInt::breadthFirstSearch() const
{
	BSTNodeInt* ptr = root;
	QueueAsArrayBSTNodeInt queue(numOfElements);
	if (ptr != nullptr) {
		queue.enqueue(ptr);
		while (!queue.isEmpty()) {
			ptr = queue.dequeue();
			ptr->visit();
			if (ptr->left != nullptr)
				queue.enqueue(ptr->left);
			if (ptr->right != nullptr)
				queue.enqueue(ptr->right);
		}
	}
}

void BSTreeInt::balance(int* data, int first, int last)
{
	if (first <= last) {
		int middle = (first + last) / 2;
		insert(data[middle]);
		balance(data, first, middle - 1);
		balance(data, middle + 1, last);
	}
}

void BSTreeInt::traversal(const BSTNodeInt* ptr, int* data, int i)
{
	if (ptr != NULL) {
		data[i-1] = ptr->getKey();
		if(ptr->right != NULL)
			traversal(ptr->right, data, 2*i);
		if(ptr->left != NULL)
			traversal(ptr->left, data, 2*i+1);
	}
}

