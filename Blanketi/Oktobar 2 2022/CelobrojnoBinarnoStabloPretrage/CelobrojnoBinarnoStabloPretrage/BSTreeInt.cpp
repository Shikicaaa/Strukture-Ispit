#include "BSTreeInt.h"

#include <exception>
using namespace std;

#include "QueueAsArrayInt.h"
#include "StackAsArrayInt.h"



void BSTreeInt::deleteTree(BSTNodeInt* ptr)
{
	if (ptr != nullptr) {
		deleteTree(ptr->left);
		deleteTree(ptr->right);
		delete ptr;
	}
}
/*
	OKTOBAR 2 2021
*/
int BSTreeInt::getNNode(BSTNodeInt* root, BSTNodeInt** maxNode, int& maxDiff)
{
	if (root == NULL) return 0;
	if (root->right == NULL && root->left == NULL) return 1;
	int left = getNNode(root->left, maxNode, maxDiff);
	int right = getNNode(root->right, maxNode, maxDiff);
	if (right - left >= 2) {
		if (right - left > maxDiff) {
			maxDiff = right - left;
			*maxNode = root;
		}
	}return 1 + (left > right ? left : right);
}
BSTNodeInt* BSTreeInt::getNNode() {
	BSTNodeInt* node = nullptr;
	int n = 0;
	getNNode(root, &node, n);
	return node;
}
/*
	JUN 2023
 */
int BSTreeInt::maxHeightDiffHelp(BSTNodeInt* root,BSTNodeInt** maxNode, int& maxDiff) {
	if (root == NULL) return 0;
	if (root->left == NULL && root->right == NULL) return 1;
	int left = maxHeightDiffHelp(root->left, maxNode, maxDiff);
	int right = maxHeightDiffHelp(root->right, maxNode,maxDiff);
	if (abs(left - right) > maxDiff){
		maxDiff = abs(left - right);
		*maxNode = root;
	}
	return 1 + (left > right ? left : right);
}
BSTNodeInt* BSTreeInt::maxHeightDiff() {
	BSTNodeInt* maxNode = nullptr;
	int n = 0;
	maxHeightDiffHelp(root, &maxNode, n);
	return maxNode;
}

/*
	OKTOBAR 2 2022
*/
BSTNodeInt* BSTreeInt::findSibling(BSTNodeInt* ptr, BSTNodeInt* p) {
	if (p == NULL) return NULL;
	if(ptr != NULL){
		//MORA BFS JER IDE PO NIVOIMA
		QueueAsArrayBSTNodeInt queue(numOfElements);
		queue.enqueue(ptr);
		bool nadjen = false;
		int brel = 1;
		while (!queue.isEmpty()) {
			// AKO JE BROJ DODATIH EL ISTI KOLKO JE I U QUEUE
			if (brel == queue.numberOfElements()) {
				//AKO JE NADJEN I IMA VISE OD 1 EL
				if (nadjen && brel > 1) {
					do {
						ptr = queue.dequeue();
						if (ptr != p) {
							return ptr;
						}
					} while (!queue.isEmpty());
				}//U SUPROTNOM NEMA BRACU I SESTRE JER JE SAM :(
				else if (nadjen) {
					return NULL;
				}
				brel = 0;
			}
			//UBACUJES ELEMENTE NAZAD U RED.
			//AKO SU NADJENI POSTAVLJA FLEG NA NADJEN I SAMO POVECAVA
			//BROJ ELEMNATA U STEKU I DODAJE IH U RED.
			ptr = queue.dequeue();
			if (ptr->left != NULL) {
				if (ptr->left == p) nadjen = true;
				queue.enqueue(ptr->left);
				++brel;
			}
			if (ptr->right != NULL) {
				if (ptr->right == p) nadjen = true;
				queue.enqueue(ptr->right);
				++brel;
			}
		}
	}
	//AKO NISTA JBG
	return NULL;
}
BSTNodeInt* BSTreeInt::findSibling(BSTNodeInt* p) {
	return findSibling(root, p);
}
/*
	SEPTEMBAR 2022
 */
int BSTreeInt::countNodesInRange(BSTNodeInt* root, int min, int max) {
	if (root == NULL) return 0;
	//AKO SE NALAZI IZMEDJU [MIN.MAX] DODAJE GA + PROVERAVA OSTALE.
	if (root->key < max && root->key > min) {
		return 1 + countNodesInRange(root->left, min, max) + countNodesInRange(root->right,min,max);
	}
	//LOGICNO JE DA AKO JE VECI OD MAXIMUMA, LEVO SU MANJI ELEMENTI
	//I ONDA PRELAZI NA LEVU GRANU, TO JE OPTIMIZACIJA KOJA JE TRAZENA
	if (root->key >= max) {
		return countNodesInRange(root->left, min, max);
	}
	//ISTO KAO I ZA LEVU, AKO JE MANJI OD MINIMUMA MORA DA PREDJE NA VECI.
	//I ONDA PRELAZI NA DESNU GRANU JER JE NA DESNOJ VECI.
	if (root->key <= min) {
		return countNodesInRange(root->right, min, max);
	}
	//AKO NISTA ONDA JBG
	return 0;
}
/*
	OKTOBAR 2022
*/
int BSTreeInt::countCloseSiblings(BSTNodeInt* root, int* n) {
	//SELF EXPLANATORY KOD BRATE
	// AKO SU NULL NEMA POTREBE DA RADI DALJE...
	if (root == NULL || root->left == NULL || root->right == NULL) {
		(*n) = 0; return *n;
	}
	//AKO JE RAZLIKA 1 POVECAVA N
	if (abs(root->left->key - root->right->key) == 1) {
		(*n) += 1;
	}
	//BROJI LEVO I DESNO PODSTABLO.
	countCloseSiblings(root->left, n);
	countCloseSiblings(root->right, n);
	//NA KRAJU VRACA SVE.
	return (*n);
}
int BSTreeInt::countCloseSiblings(BSTNodeInt* root)
{
	int n = 0;
	countCloseSiblings(root, &n);
	return n;
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
		root = new BSTNodeInt(el);
	else if (par->isLT(el))
		par->right = new BSTNodeInt(el);
	else
		par->left = new BSTNodeInt(el);
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
