//
//  binaryNode.hpp
//  
//
//  Created by Daniel Nizam on 11/30/16.
//
//

#ifndef binaryNode_hpp
#define binaryNode_hpp

class BinaryNode
{
    char latinAlphabet;
    BinaryNode *leftNode;
    BinaryNode *rightNode;
    
public:
    BinaryNode();
    char getLatinAlphabet();
    BinaryNode *getLeftNode();
    BinaryNode *getRightNode();
    void setLatinAlphabet(char al);
    void setLeftNode(BinaryNode *left);
    void setRightNode(BinaryNode *right);
};


    #endif /* binaryNode_hpp */
