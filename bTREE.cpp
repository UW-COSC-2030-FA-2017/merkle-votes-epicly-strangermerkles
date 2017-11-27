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

int bTREE::dataInserted(treeNode* tree1) const 
{
	if (tree1->leftNode == NULL && tree1->rightNode == NULL && tree1->leaf == true) {
		return 1;
	}
	else {
		return dataInserted(tree1->rightNode) + dataInserted(tree1->leftNode);
	}
}

int bTREE::numberOfNodes() const//****
{
	return numberOfNodes(getTree());
}

int bTREE::numberOfNodes(treeNode* tree1) const
{
	if (tree1->leftNode == NULL && tree1->rightNode == NULL) {
		return 1;
	}
	else {
		return 1 + numberOfNodes(tree1->rightNode) + numberOfNodes(tree1->leftNode);
	}
}

bTREE::treeNode* bTREE::insert2(treeNode* temp, treeNode* newnode)
{
	if (temp == NULL) {
		temp = newnode;
	}
	else {
		int lheight = height(temp->leftNode);
		int rheight = height(temp->rightNode);

		if (lheight <= rheight) {
			insert2(temp->leftNode, newnode);
			if (temp->leftNode == NULL) {
				treeNode* temp2 = new treeNode();
				temp->leftNode = newnode;
				temp2->data = temp->data;
				temp2->time = temp->time;
				temp2->leaf = true;
				temp->rightNode = temp2;
				temp->data = "0";
				temp->leaf = false;
				temp->leftNode->parent = temp;
				temp->rightNode->parent = temp;
			}
		}
		else {
			insert2(temp->rightNode, newnode);
			if (temp->rightNode == NULL) {
				treeNode* temp2 = new treeNode();
				temp->leftNode = newnode;
				temp2->data = temp->data;
				temp2->time = temp->time;
				temp2->leaf = true;
				temp->rightNode = temp2;
				temp->data = "0";
				temp->leaf = false;
				temp->leftNode->parent = temp;
				temp->rightNode->parent = temp;
			}
		}
	}
	return temp;
}

int bTREE::insert(string data1, int time1)
{
	treeNode* tree2 = new treeNode();
	treeNode* temp = tree;
	tree2->leaf = true;
	tree2->time = time1;
	tree2->data = data1;
	tree = insert2(temp, tree2);
	return 1;
}

bTREE::treeNode* bTREE::getTree() const 
{
	return tree;
}

int bTREE::height(treeNode* tree1) const
{
	if (tree1 == NULL)
		return 0;
	//Uses taller height
	int lheight = height(tree1->leftNode);
	int rheight = height(tree1->rightNode);

	if (lheight > rheight)
		return 1 + lheight;
	else
		return 1 + rheight;
}

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

int bTREE::find(string data, int time, treeNode* node, bool& found) const
{
	int count = 1;
	if (node->data == data && node->time == time) {
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

bool operator ==(const bTREE& lhs, const bTREE& rhs)
{
	if (lhs.height(lhs.getTree()) != rhs.height(rhs.getTree())) {
		return false;
	}
	else if (lhs.numberOfNodes(lhs.getTree()) != rhs.numberOfNodes(rhs.getTree())) {
		return false;
	}
	return rhs.checkEquality(lhs.getTree(), rhs.getTree());
}

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
		displayLeft(out, node->leftNode, "       ");
		out << "-------" << node->data << endl;
		displayRight(out, node->rightNode, "       ");
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
		displayLeft(out, subtree->leftNode, prefix + "         ");
		out << prefix + "/-------" << subtree->data << endl;
		displayRight(out, subtree->rightNode, prefix + "|        ");
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
		displayLeft(outfile, subtree->leftNode, prefix + "|        ");
		outfile << prefix + "\\-------" << subtree->data << endl;
		displayRight(outfile, subtree->rightNode, prefix + "         ");
	}
}