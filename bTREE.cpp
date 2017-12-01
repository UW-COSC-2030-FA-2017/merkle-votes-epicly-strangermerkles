#include "bTREE.h"


//look at descriptions in pMT.h for guidance on what you might need for these function to actually do
bTREE::bTREE()
{
	tree = NULL;
}

bTREE::~bTREE()
{
	clearNode(tree);
}

void bTREE::clearNode(treeNode* tree1) 
{
	if (tree1 != NULL) {
		if (tree1->leftNode != NULL) {
			clearNode(tree1->leftNode);
		}
		if (tree1->rightNode != NULL) {
			clearNode(tree1->rightNode);
		}
		delete tree1;
	}
}

int bTREE::dataInserted() const//****
{
	return dataInserted(getTree());
}

// Returns the number of leaf nodes in the tree
int bTREE::dataInserted(treeNode* tree1) const 
{
	if (tree1->leftNode == NULL && tree1->rightNode == NULL && tree1->leaf == true) {
		return 1;
	}
	else {
		return dataInserted(tree1->rightNode) + dataInserted(tree1->leftNode);
	}
}

// Returns the number of nodes in the tree
int bTREE::numberOfNodes() const//****
{
	return numberOfNodes(getTree());
}

// Helper function that returns the number of nodes in the tree
int bTREE::numberOfNodes(treeNode* tree1) const
{
	if (tree1->leftNode == NULL && tree1->rightNode == NULL) {
		return 1;
	}
	else {
		return 1 + numberOfNodes(tree1->rightNode) + numberOfNodes(tree1->leftNode);
	}
}

// Helper function that inserts data into the tree, only on the leaf node
bTREE::treeNode* bTREE::insert2(treeNode* temp, treeNode* newnode,int& count)
{
	count += 1;
	// Only check left node because we move the root node to the rightNode so there will never be a right node empty at this height
	if (temp->leftNode == NULL) {
		bTREE::treeNode* temp2 = new bTREE::treeNode();
		temp->leftNode = newnode;
		temp2->data = temp->data;
		temp2->time = temp->time;
		temp2->leaf = true;
		temp2->height = 1;
		temp->rightNode = temp2;
		temp->height = 2;
		temp->data = "0";
		temp->time = 0;
		temp->leaf = false;
		temp->leftNode->parent = temp;
		temp->rightNode->parent = temp;
		count += 1;					// Increment one more time because I need to move the root node to a leaf

		bool heightIncrease = true;

		// The height is changed only when the left and right nodes have the same height, else it keeps the height of the lowest tree
		while (temp->parent != NULL && heightIncrease == true) {
			if (heightIncrease == true) {
				if (temp->parent->rightNode->height == temp->parent->leftNode->height) {
					temp->parent->height = (temp->parent->height) + 1;
				}
				else {
					heightIncrease = false;
				}
			}
			temp = temp->parent;
			count++;
		}
	}
	else {
		int lheight = temp->leftNode->height;
		int rheight = temp->rightNode->height;

		if (lheight <= rheight) {
			insert2(temp->leftNode, newnode, count);
		}
		else {
			insert2(temp->rightNode, newnode, count);
		}
	}
	return temp;
}

// Insert data into a tree
// Data only exists on the leaf nodes
int bTREE::insert(string data1, int time1)
{
	int count = 1;
	treeNode* tree2 = new treeNode();
	tree2->leaf = true;
	tree2->time = time1;
	tree2->data = data1;
	tree2->height = 1;
	if (tree == NULL) {
		tree = tree2;
	}
	else {
		tree = insert2(tree, tree2, count);
	}
	return count;
}

// Return the tree
bTREE::treeNode* bTREE::getTree() const 
{
	return tree;
}

// Finds a set of data and a time in the tree
int bTREE::find(string data, int time) const

{
	bool found = false;
	int count = find(data, time, tree, found);
	if (found == false) {
		return 0;
	}
	else {
		return count;
	}
}

// Helper function that finds a set of data and a time in the tree
// Time -1 is a default value if no time is entered
int bTREE::find(string data, int time, treeNode* node, bool& found) const
{
	int count = 1;
	if (node->data == data && (node->time == time || time == -1)) {
		found = true;
		return count;
	}
	if (node->leftNode != NULL && found == false) {
		count += find(data, time, node->leftNode, found);
	}
	if (node->rightNode != NULL && found == false) {
		count += find(data, time, node->rightNode, found);
	}
	return count;
}

// Locates the left and right positon to find a value in the tree
string bTREE::locate(string data) const
{
	string temp = locate(data, getTree(), "");
	if (temp == "") {
		return ".";
	}
	else {
		return temp;
	}
}

// Helper function that locates the left and right positon to find a value in the tree
string bTREE::locate(string data, treeNode* node, string returnLocate) const 
{
	string left = "", right = "";
	if (node->data == data) {
		return returnLocate;
	}
	if (node->leftNode != NULL) {
		left = locate(data, node->leftNode, returnLocate + "L");
	}
	if (node->rightNode != NULL) {
		right = locate(data, node->rightNode, returnLocate + "R");
	}
	if (left == "") {
		return right;
	}
	else {
		return left;
	}
}


// Returns the root of the tree
string bTREE::getRoot() const
{
	return tree->data;
}

// Equality operation
// Compares each node of the lhs tree with the node of the rhs tree
// Checks the number of nodes and height first to eliminate easy checks
bool operator ==(const bTREE& lhs, const bTREE& rhs)
{
	int count = 0;
	if (lhs.getTree()->height != rhs.getTree()->height) {
		return false;
	}
	else if (lhs.numberOfNodes(lhs.getTree()) != rhs.numberOfNodes(rhs.getTree())) {
		return false;
	}
	return rhs.checkEquality(lhs.getTree(), rhs.getTree());
}

// Helper function that compares the nodes of two trees
bool bTREE::checkEquality(treeNode* lhs, treeNode* rhs) const
{
	if (lhs == NULL || rhs == NULL) {
		return true;
	}
	if (lhs->leaf == rhs->leaf && lhs->data == rhs->data && lhs->time == rhs->time) {
		if (checkEquality(lhs->leftNode, rhs->leftNode) == true && checkEquality(lhs->rightNode, rhs->rightNode) == true) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

// Not equal operator, simply returns the not of the equal operation
bool operator !=(const bTREE& lhs, const bTREE& rhs)
{
	return !(lhs == rhs);
}

// Prints out the data element of the nodes in a tree
ostream& operator <<(ostream& out, const bTREE& p)
{
	return p.display(out, p.getTree());
}

// Display the nodes of a tree.
ostream& bTREE::display(ostream& out, treeNode* node) const 
{
	string prefix;
	if (node == NULL) {
		out << "-" << endl;
	}
	else {
		displayLeft(out, node->leftNode, "           ");
		out << "---------" << node->data << endl;
		displayRight(out, node->rightNode, "           ");
	}
	return out;
}

// Display the nodes connected to the left subtree.
// Adpapted from lab8
void bTREE::displayLeft(ostream& out, treeNode* subtree, string prefix) const
{
	if (subtree == NULL) {
		out << prefix + "/" << endl;
	}
	else {
		displayLeft(out, subtree->leftNode, prefix + "           ");
		out << prefix + "/---------" << subtree->data << endl;
		displayRight(out, subtree->rightNode, prefix + "|           ");
	}
}

// Display the nodes connected to the right subtree.
// Adpapted from lab8
void bTREE::displayRight(ostream & outfile, treeNode* subtree, string prefix) const
{
	if (subtree == NULL) {
		outfile << prefix + "\\" << endl;
	}
	else {
		displayLeft(outfile, subtree->leftNode, prefix + "|           ");
		outfile << prefix + "\\---------" << subtree->data << endl;
		displayRight(outfile, subtree->rightNode, prefix + "           ");
	}
}