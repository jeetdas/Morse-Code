//
//  morseClass.cpp
//  
//
//  Created by Daniel Nizam on 11/30/16.
//
//

#include "morseClass.hpp"

//creates a binary tree for the letters in morse code
BinaryNode* morseClass::createBinaryTree(BinaryNode *root, int height)
{
    if (height <= 0)
    {
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
                root->setLeftNode(createBinaryTree(root->getLeftNode(), height-1));
            }
            //#omp section
            {
                root->setRightNode(createBinaryTree(root->getRightNode(), height-1));
            }
        }
    }
    return root;
}

BinaryNode* morseClass::createBinaryTree(int height)
{
    BinaryNode *root = new BinaryNode();
    root = createBinaryTree(root, height+1);
	BinaryNode *temp;
	for (std::map <char, std::string>::iterator it = morseCharacterMap.begin(); it != morseCharacterMap.end(); ++it)
	{
		temp = root;
		for (int i = 0; i < ((*it).second).length(); ++i)
		{
			if (((*it).second)[i] == '.')
				temp = temp->getLeftNode();
			else
				temp = temp->getRightNode();
		}
		temp->setLatinAlphabet((*it).first);
	}
    return root;
}

//reads in the file of letters to their morse code symbols
int morseClass::readMorseCodeInputFile(std::string fileName)
{
    char key;
    std::string value;
    int maxLength = 0;
    std::ifstream fin(fileName);
    while (!fin.eof())
    {
        fin >> key;
		validKeys.push_back(key);
        fin >> value;
        if (value.length() > maxLength)
            maxLength = value.length();
        morseCharacterMap[key] = value;
    }
    fin.close();
    return maxLength;
}

void morseClass::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

std::vector<std::string> morseClass::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

//converts the letters given from the user and converts them to morse code and outputs to the user
void morseClass::latinToMorse()
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
		if (validKey(c))
			morseStr += morseCharacterMap[c] + " ";
		else
		{
			std::cerr << "Invalid character. Character not present in table. Try again." << std::endl;
			return;
		}
    }
    
    std::cout << "Converted string = " << morseStr << std::endl;
}

//converts the morse code given from a user to converts it to letters
void morseClass::morseToLatin(BinaryNode *root)
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
			if (temp == nullptr)
			{
				std::cerr << "Invalid morse code, please try again." << std::endl;
				return;
			}
            else if (*it == '.')
            {
                temp = temp->getLeftNode();
                //std::cout << "2" << temp->latinAlphabet << std::endl;
            }
            else if (*it == '_')
            {
                temp = temp->getRightNode();
                //std::cout << "2" << temp->latinAlphabet << std::endl;
            }
			else
			{
				std::cerr << "Invalid morse code, please try again." << std::endl;
				return;
			}
            //std::cout << "3" << temp->latinAlphabet << std::endl;
        }
        //std::cout << "lala 1 = " << latinStr << std::endl;
        latinStr += temp->getLatinAlphabet();
        //std::cout << "lala 2 = " << latinStr << std::endl;
    }
    
    std::cout << "Converted string = " << latinStr << std::endl;
}

void morseClass::menu(BinaryNode *root)
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
                latinToMorse();
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

void morseClass::printBinaryTree(BinaryNode *root)
{
    std::cout << "VAL " << root->getRightNode()->getLeftNode()->getLeftNode()->getLeftNode()->getLatinAlphabet() << std::endl;
}

void morseClass::putValueInMorseMap(char c, std::string val)
{
	// Add try and catch
	morseCharacterMap[c] = val;
}
std::string morseClass::getValueInMorseMap(char c)
{
	// Check if exists, else return -1
	return morseCharacterMap[c];
}

void morseClass::putInValidKeys(char c)
{
	validKeys.push_back(c);
}
bool morseClass::validKey(char c)
{
	// Check if c in validKeys vector
	if (std::find(validKeys.begin(), validKeys.end(), c) != validKeys.end())
		return true;
	else
		return false;
	
}
