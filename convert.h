#ifndef CONVERT_H
#define CONVERT_H
#pragma once
#include "parser.h"

extern std::map<std::string, TokenType> reserved_words;

class Convert {
private:
	std::deque<Token> postfixTokens;
public: 
	Convert(const std::deque<Token> tokens) : postfixTokens(tokens) {}
	void compileLiteral(const char*& s);
	void compileSymbol(const char*& s);
	void compileExpression(const char*& s);
	void compileTerm(const char*& s);
	void compileMulDiv(const char*& s);
	void compileAddSub(const char*& s);
};

#endif
