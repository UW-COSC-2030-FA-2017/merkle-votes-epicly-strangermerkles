#include "pMT.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

pMT* readFile(string);
void validate(const pMT & lhs, const pMT & rhs);
void printRoot(const pMT & lhs);

int main(int argc, char **argv)
{
	pMT* votes1 = readFile("mv_test.txt");
	//cout << "Displaying the first set of votes:\n" << *votes1;

	pMT* votes2 = readFile("mv_test.txt");
	//cout << "Displaying the second set of votes (same as the first):\n" << *votes2;

	pMT* votes3 = readFile("mv1_test.txt");
	//cout << "Displaying the third set of votes (different than the previous two:\n" << *votes3;

	cout << "Comparing the first and second voting files: ";
	validate(*votes1, *votes2);
	cout << "\n";
	cout << "Comparing the first and third voting files: ";
	validate(*votes1, *votes3);
	cout << "\n";

	cout << "Root node of first voting files\n";
	printRoot(*votes1);
	cout << "\nRoot node of second voting files\n";
	printRoot(*votes2);
	cout << "\nRoot node of third voting files\n";
	printRoot(*votes3);
	return 0;
}

pMT* readFile(string file)
{
	pMT* votes = new pMT();
	ifstream inFile;
	string tempVote;
	int tempTime;

	inFile.open(file);
	if (!inFile)
	{
		cerr << "Cannot open input: " << file<< endl;
		inFile.clear();
		return votes;
	}
	
	inFile >> tempVote;
	inFile >> tempVote; // Reads in the first line of the file and ignores it

	while (!inFile.eof())
	{
		inFile >> tempVote;
		inFile >> tempTime;
		votes->insert(tempVote, tempTime);
	}

	inFile.close();
	return votes;
}

void validate(const pMT & lhs, const pMT & rhs)
{
	bool vote = (lhs == rhs);
	if (vote == 1) {
		cout << "Items are Validated\n";
	}
	else {
		cout << "Items are Not Validated\n";
	}
}

void printRoot(const pMT & lhs)
{
	cout << "Root node: " << lhs.getRoot();
}