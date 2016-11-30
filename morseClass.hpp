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

class morseClass{
public:
    morseClass();
    BinaryNode* createBinaryTree(BinaryNode *root, int height);
    BinaryNode *createBinaryTree(int height);
    std::pair <std::map <char, std::string>, int> readMorseCodeInputFile(std::string fileName);
    void split(const std::string &s, char delim, std::vector<std::string> &elems);
    std::vector<std::string> split(const std::string &s, char delim);
    void latinToMorse(std::map <char, std::string> morseCharacterMap);
    void morseToLatin(BinaryNode *root);
    void menu(std::map <char, std::string> morseCharacterMap, BinaryNode *root);
    void printBinaryTree(BinaryNode *root);
    
private:
    int BinaryNode;
    
    
};

#endif /* morseClass_hpp */
