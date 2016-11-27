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

BinaryNode* createBinaryTree(BinaryNode *root, int height)
{
	if (height <= 0)
	{
		++BinaryNode::count;
		//std::cout << "Number of ends reached = " << BinaryNode::count << std::endl;
		return NULL;
	}
	else
	{
		root = new BinaryNode();
		//#omp sections
		{
			//#omp section
			{
				root->leftNode = createBinaryTree(root->leftNode, height-1);	
			}
			//#omp section
			{
				root->rightNode = createBinaryTree(root->rightNode, height-1);
			}
		}
	}
	return root;
}

BinaryNode *createBinaryTree(int height)
{
	BinaryNode *root;
	root = createBinaryTree(root, height+1);
	return root;
}

std::pair <std::map <char, std::string>, int> readMorseCodeInputFile(std::string fileName)
{
	std::map <char, std::string> morseCharacterMap;
	char key;
	std::string value;
	int maxLength = 0;
	std::ifstream fin(fileName);
	while (!fin.eof())
	{
		fin >> key;
		fin >> value;
		if (value.length() > maxLength)
			maxLength = value.length();
		morseCharacterMap[key] = value;
	}
	fin.close();
	std::pair <std::map <char, std::string>, int> returnVal (morseCharacterMap, maxLength);
	return returnVal;
}

// ###########################
void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
// ###########################

void latinToMorse(std::map <char, std::string> morseCharacterMap)
{
	std::string str, morseStr;
	char c;
	std::cout << "Enter string to encode" << std::endl;
	getline(std::cin, str);
	getline(std::cin, str);

	morseStr = "";

	for (std::string::iterator it = str.begin(); it != str.end(); ++it)
	{
		c = tolower(*it);
		morseStr += morseCharacterMap[*it] + " ";
	}

	std::cout << "Converted string = " << morseStr << std::endl;
}

void morseToLatin(BinaryNode *root)
{
	std::string str, latinStr;
	BinaryNode *temp;
	std::cout << "Enter string (separated by spaces between characters) to decode" << std::endl;
	getline(std::cin, str);
	getline(std::cin, str);

	latinStr = "";

	std::vector<std::string> splitString = split(str, ' ');

	for (std::vector<std::string>::iterator itt = splitString.begin(); itt != splitString.end(); ++itt)
	{
		temp = root;
		//std::cout << "vector ele = "  << "|" << (*itt) << "|" << std::endl;
		for (std::string::iterator it = (*itt).begin(); it != (*itt).end(); ++it)
		{
			//std::cout << "1 " << temp->latinAlphabet << std::endl;
			if (*it == '.')	
			{
				temp = temp->leftNode;
				//std::cout << "2" << temp->latinAlphabet << std::endl;
			}
			else
			{
				temp = temp->rightNode;
				//std::cout << "2" << temp->latinAlphabet << std::endl;
			}
			//std::cout << "3" << temp->latinAlphabet << std::endl;
		}
		//std::cout << "lala 1 = " << latinStr << std::endl;
		latinStr += temp->latinAlphabet;
		//std::cout << "lala 2 = " << latinStr << std::endl;
	}

	std::cout << "Converted string = " << latinStr << std::endl;
}

void menu(std::map <char, std::string> morseCharacterMap, BinaryNode *root)
{
	while (true)
	{
		int opt = 0;
		std::cout << "MENU" << std::endl;
		std::cout << "1. Convert latin text to Morse Code" << std::endl;
		std::cout << "2. Convert Morse Code to latin text" << std::endl;
		std::cout << "3. Quit" << std::endl;
		std::cin >> opt;
		
		switch(opt)
		{
			case 1:
				latinToMorse(morseCharacterMap);
			break;
			case 2:
				morseToLatin(root);
			break;
			case 3:
				exit(0);
			default:
				std::cerr << "Invalid menu option, please try again" << std::endl;
		}
	}
}

void printBinaryTree(BinaryNode *root)
{
	std::cout << "VAL " << root->rightNode->leftNode->leftNode->leftNode->latinAlphabet << std::endl;
}

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