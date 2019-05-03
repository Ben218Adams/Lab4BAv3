#pragma once

#include <string>

struct ParseNode {
	char value;
	ParseNode* left;
	ParseNode* right;
	ParseNode() { left = right = nullptr; }
};

class ParseTree
{
public:
	ParseTree();
	ParseTree(std::string expression = "");
	virtual ~ParseTree();
	std::string inOrder();
	std::string postOrder();
	std::string preOrder();
	std::string troubleshoot();
private:
	ParseNode* root;

	ParseNode* doParse(std::string exp);
	void recDestruct(ParseNode* ptr);
	std::string recInOrder(ParseNode* ptr);
	std::string recPostOrder(ParseNode* ptr);
	std::string recPreOrder(ParseNode* ptr);
	bool isOperator(char value);
	bool isOperand(char value);

	static const char LPAREN = '(';
	static const char RPAREN = ')';
	static const char PLUS = '+';
	static const char MINUS = '-';
	static const char MULT = '*';
	static const char DIV = '/';
	static const char SPACE = ' ';
};

