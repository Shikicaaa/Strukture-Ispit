#include "BSTreeInt.h"

void main()
{
    BSTreeInt drvo;
    drvo.insert(50);
    drvo.insert(30);
    drvo.insert(70);
    drvo.insert(20);
    drvo.insert(40);
    drvo.insert(60);
    drvo.insert(80);
    drvo.insert(10); 
    drvo.insert(25); 
    drvo.insert(35); 
    drvo.insert(45); 
    drvo.insert(55); 
    drvo.insert(65); 
    drvo.insert(75); 
    drvo.insert(85);
    drvo.insert(9);
    drvo.insert(11);
    drvo.insert(8);
    std::cout <<"Count Smaller: " <<  drvo.countSmaller(10);
    std::cout << "\nCount Close Parents: " << drvo.countCloseParents(6);
    std::cout << "\nBiggest Absolute Value: " << drvo.maxAbsBetweenSubtrees()->key;
    std::cout << "\nBiggest even-odd value: " << drvo.razlikaSume()->key;
    std::cout << "\nPobede domacih: " << drvo.countNodes();
}
