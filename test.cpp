#include "pMT.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
	cout << "Inserting elements into a binary tree.\n";
	bTREE tree1 = bTREE();
	tree1.insert("a", 1);
	tree1.insert("b", 2);
	tree1.insert("c", 3);
	tree1.insert("d", 4);
	tree1.insert("e", 5);
	tree1.insert("f", 6);

	cout << "Displaying the tree:\n";
	cout << tree1 << endl;

	cout << "Displaying the number of data entries in the tree: "
	     << tree1.dataInserted() << endl;
	cout << "Displaying the number of nodes in the tree: "
		 << tree1.numberOfNodes() << endl << endl;

	cout << "Path for locating e is: " << tree1.locate("e") << endl;
	cout << "Path for locating f is: " << tree1.locate("f") << endl;
	cout << "Path for locating j is: " << tree1.locate("j") << endl << endl;

	cout << "Number of operations to find e is: " << tree1.find("e") << endl;
	cout << "Number of operations to find f is: " << tree1.find("f") << endl;
	cout << "Number of operations to find j is: " << tree1.find("j") << endl;
	cout << "Number of operations to find a is: " << tree1.find("a") << endl;
	cout << "Number of operations to find b is: " << tree1.find("b") << endl << endl;

	cout << "Inserting elements into a second binary tree.\n";
	bTREE tree2 = bTREE();
	tree2.insert("a", 1);
	tree2.insert("b", 2);
	tree2.insert("c", 3);
	tree2.insert("d", 4);
	tree2.insert("e", 5);
	tree2.insert("f", 6);

	cout << "Displaying the tree:\n";
	cout << tree2 << endl;

	cout << "Comparing the first and second tree for equality: " << (tree1 == tree2) << endl;
	cout << "Comparing the first and second tree for inequality: " << (tree1 != tree2) << endl;

	cout << "Inserting elements into a third binary tree.\n";
	bTREE tree3 = bTREE();
	tree3.insert("a", 1);
	tree3.insert("b", 2);
	tree3.insert("c", 3);
	tree3.insert("d", 4);
	tree3.insert("e", 5);
	tree3.insert("g", 6);

	cout << "Displaying the tree:\n";
	cout << tree3 << endl;

	cout << "Comparing the first and third tree for equality: " << (tree1 == tree3) << endl;
	cout << "Comparing the first and third tree for inequality: " << (tree1 != tree3) << endl << endl;

	cout << "********************************************************\n";
	cout << "Inserting elements into a merkle tree.\n";
	pMT mtree1 = pMT();
	mtree1.insert("a", 1);
	mtree1.insert("b", 2);
	mtree1.insert("c", 3);
	mtree1.insert("d", 4);
	mtree1.insert("e", 5);
	mtree1.insert("f", 6);

	cout << "Displaying the tree:\n";
	cout << mtree1 << endl;

	cout << "Path for locating e is: " << mtree1.locateData("e") << endl;
	cout << "Path for locating f is: " << mtree1.locateData("f") << endl;
	cout << "Path for locating j is: " << mtree1.locateData("j") << endl;
	cout << "Path for locating 5863375 is: " << mtree1.locateHash("5863375") << endl << endl;

	cout << "Number of operations to find 5863375 is: " << mtree1.findHash("5863375") << endl;
	cout << "Number of operations to find e 5 is: " << mtree1.find("e", 5) << endl;
	cout << "Number of operations to find f 7 is: " << mtree1.find("f", 7) << endl << endl;

	cout << "Inserting elements into a second merkle tree.\n";
	pMT mtree2 = pMT();
	mtree2.insert("a", 1);
	mtree2.insert("b", 2);
	mtree2.insert("c", 3);
	mtree2.insert("d", 4);
	mtree2.insert("e", 5);
	mtree2.insert("f", 6);

	cout << "Displaying the tree:\n";
	cout << mtree2 << endl;

	cout << "Comparing the first and second tree for equality: " << (mtree1 == mtree2) << endl;
	cout << "Comparing the first and second tree for inequality: " << (mtree1 != mtree2) << endl;

	cout << "Inserting elements into a third merkle tree.\n";
	pMT mtree3 = pMT();
	mtree3.insert("a", 1);
	mtree3.insert("b", 2);
	mtree3.insert("c", 3);
	mtree3.insert("d", 4);
	mtree3.insert("e", 5);
	mtree3.insert("g", 6);

	cout << "Displaying the tree:\n";
	cout << mtree3 << endl;

	cout << "Comparing the first and third tree for equality: " << (mtree1 == mtree3) << endl;
	cout << "Comparing the first and third tree for inequality: " << (mtree1 != mtree3) << endl;
	cout << "Displaying where two trees are different: " << (mtree1 ^ mtree3) << endl;
	return 0;
}
