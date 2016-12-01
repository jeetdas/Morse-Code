//
//  morseClass.hpp
//  
//
//  Created by Daniel Nizam on 11/30/16.
//
//

#ifndef morseClass_hpp
#define morseClass_hpp

#include <stdio.h>
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
#include <algorithm>

#include "binaryNode.hpp"

class morseClass{
public:
    //morseClass();
    BinaryNode* createBinaryTree(int height);
    int readMorseCodeInputFile(std::string fileName);
    void latinToMorse();
    void morseToLatin(BinaryNode *root);
    void menu(BinaryNode *root);
	void printBinaryTree(BinaryNode *root);
	void putValueInMorseMap(char c, std::string val);
	std::string getValueInMorseMap(char c);
	void putInValidKeys(char);
	bool validKey(char);
    
private:
    //BinaryNode* root;
    BinaryNode* createBinaryTree(BinaryNode *root, int height);
    void split(const std::string &s, char delim, std::vector<std::string> &elems);
    std::vector<std::string> split(const std::string &s, char delim);
	std::map<char, std::string> morseCharacterMap;
	std::vector<char> validKeys;
};

#endif /* morseClass_hpp *///
