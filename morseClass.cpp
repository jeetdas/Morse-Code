//
//  morseClass.cpp
//  
//
//  Created by Daniel Nizam on 11/30/16.
//
//

#include "morseClass.hpp"

//creates a binary tree for the letters in morse code
morseClass::BinaryNode* createBinaryTree(BinaryNode *root, int height)
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

morseClass::BinaryNode *createBinaryTree(int height)
{
    BinaryNode *root;
    root = createBinaryTree(root, height+1);
    return root;
}

//reads in the file of letters to their morse code symbols
std::pair <std::map <char, std::string>, int> morseClass::readMorseCodeInputFile(std::string fileName)
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
void morseClass::latinToMorse(std::map <char, std::string> morseCharacterMap)
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

void morseClass::menu(std::map <char, std::string> morseCharacterMap, BinaryNode *root)
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

void morseClass::printBinaryTree(BinaryNode *root)
{
    std::cout << "VAL " << root->rightNode->leftNode->leftNode->leftNode->latinAlphabet << std::endl;
}


