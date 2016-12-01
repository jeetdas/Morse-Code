//
//  binaryNode.cpp
//  
//
//  Created by Daniel Nizam on 11/30/16.
//
//

#include "binaryNode.hpp"

BinaryNode::BinaryNode()
{
    char latinAlphabet = '\0';
    leftNode = NULL;
    rightNode = NULL;
}

char BinaryNode::getLatinAlphabet()
{
    return latinAlphabet;
}

BinaryNode* BinaryNode::getLeftNode()
{
    return leftNode;
}

BinaryNode* BinaryNode::getRightNode()
{
    return rightNode;
}


void BinaryNode::setLatinAlphabet(char al)
{
    latinAlphabet = al;
}

void BinaryNode::setLeftNode(BinaryNode *left)
{
    leftNode = left;
}

void BinaryNode::setRightNode(BinaryNode *right)
{
    rightNode = right;
}
