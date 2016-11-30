#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctype.h>
#include <sstream>
#include "morseClass.hpp"

struct BinaryNode
{
	char latinAlphabet;
	BinaryNode *leftNode;
	BinaryNode *rightNode;

	static int count;

	BinaryNode()
	{
		char latinAlphabet = '\0';
		leftNode = NULL;
		rightNode = NULL;
	}
};

int BinaryNode::count = 0;

int main()
{

	std::pair <std::map <char, std::string>, int> readFile = readMorseCodeInputFile("morse.txt");
	BinaryNode *r = createBinaryTree(readFile.second);
	BinaryNode *temp;
	for (std::map <char, std::string>::iterator it = readFile.first.begin(); it != readFile.first.end(); ++it)
	{
		temp = r;
		for (int i = 0; i < ((*it).second).length(); ++i)
		{
			if (((*it).second)[i] == '.')
				temp = temp->leftNode;
			else
				temp = temp->rightNode;
		}
		temp->latinAlphabet = (*it).first;
	}

	//printBinaryTree(r);

	menu(readFile.first, r);

	return 0;
}
