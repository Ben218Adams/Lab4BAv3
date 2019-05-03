#include "ParseTree.h"

#include "ParseTree.h"
#include <stack>
#include <cctype>
#include <iostream>
#include<sstream>


ParseTree::ParseTree()
{
	this->root = nullptr; 
}

// constructor, build tree from expression
ParseTree::ParseTree(std::string expression)
{
	root = doParse(expression);
}

// desctructor, delete nodes in tree
ParseTree::~ParseTree()
{
	recDestruct(root);
}

// inorder traversal
std::string ParseTree::inOrder()
{
	return recInOrder(root); 
}

// postorder traversal
std::string ParseTree::postOrder()
{
	return recPostOrder(root);
}

// preorder traversal
std::string ParseTree::preOrder()
{
	return recPreOrder(root);
}

// helper function for doParse, true if valueis operator(+ - * /)
bool ParseTree::isOperator(char value)
{
	if (value == PLUS || value == MINUS || value == MULT || value == DIV)
		return true;
	else
		return false;
}

// helper function for doParse, true if value is letter or digit
bool ParseTree::isOperand(char value)
{
	return isalnum(value);          // Built in cpp finc, alnum = alphanumeric
}

// helper method to do the parsing and save tree
ParseNode* ParseTree::doParse(std::string exp)
{
	std::stack<ParseNode*> theStack;
	std::string buffer = "";
	int i = 0;
	while (exp[i] != '\0')
	{
		char next = exp[i];
		if (next == SPACE)
		{
			continue;       // skip over white space
		}
		else if (isOperand(next))            //If	an	operand create a new node for operand, push it on the stack
		{
			ParseNode* opnode = new ParseNode;
			opnode->value = next;
			theStack.push(opnode);
		}
		else if (isOperator(next))
		{
			ParseNode* operatorNode = new ParseNode;
			operatorNode->value = next;             // new operator parse node
			operatorNode->right = theStack.top();
			theStack.pop();                         // pop stack to right of operator node
			operatorNode->left = theStack.top();
			theStack.pop();                         // pop stack to left of operator node
			theStack.push(operatorNode);            // push operator node to stack
		}
		i++;
	}
	ParseNode* theRoot = theStack.top();
	theStack.pop();  // this is not necessary
	return theRoot;
}

// recursive helper methods
void ParseTree::recDestruct(ParseNode * ptr)
{
	if (ptr == nullptr)
		return; 
	if (ptr->left != nullptr)
		recDestruct(ptr->left);
	if (ptr->right != nullptr)
		recDestruct(ptr->right);
	delete ptr;
}

std::string ParseTree::recInOrder(ParseNode * ptr)
{
	std::string buffer = "";
	if (ptr = nullptr)
		return buffer;
	if (ptr->left != nullptr)       //segmentation fault try stringstream?
		buffer += recInOrder(ptr->left);
	buffer += ptr->value;
	if (ptr->right != nullptr)
		buffer += recInOrder(ptr->right);
	return buffer;
}

std::string ParseTree::recPostOrder(ParseNode * ptr)
{
	std::ostringstream ss;
	if (ptr->left != nullptr)       //doesnt help
		ss << recPostOrder(ptr->left);
	if (ptr->right != nullptr)
		ss << recPostOrder(ptr->right);
	ss << ptr->value;
	return ss.str();
}

std::string ParseTree::recPreOrder(ParseNode * ptr)
{
	std::string buffer = "";
	buffer += ptr->value;
	if (ptr->left != nullptr)       //segmentation fault try stringstream?
		buffer += recPreOrder(ptr->left);
	if (ptr->right != nullptr)
		buffer += recPreOrder(ptr->right);
	return buffer;
}

std::string ParseTree::troubleshoot()
{
	return "Give up";
}


