#include "BSTreeInt.h"

void main()
{
	BSTreeInt stablo;
	stablo.insert(10);
	stablo.insert(7);
	stablo.insert(15);
	stablo.insert(6);
	stablo.insert(8);
	stablo.insert(5);
	stablo.insert(4);
	stablo.insert(13);
	stablo.insert(16);
	stablo.insert(17);
	stablo.insert(18);
	stablo.insert(19);
	stablo.insert(11);
	stablo.insert(14);
	std::cout << stablo.getNNode()->getKey();
	std::cout << stablo.maxHeightDiff()->key << endl;
	BSTNodeInt* node = stablo.findSibling(stablo.search(15));
	if (node != NULL) std::cout << node->key << endl;
	else std::cout << "NULL" << endl;
	std::cout << stablo.countCloseSiblings(stablo.search(10)) << endl;
	std::cout << stablo.countNodesInRange(stablo.search(10), 9, 15) << endl;
}
