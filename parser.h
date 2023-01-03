#ifndef PARSER_H
#define PARSER_H
#pragma once
#include <vector>
#include "lexer.h"

extern std::map<std::string, TokenType> reserved_words;

class Parser {
private:
	std::vector<Token> tokens;
	int pos;

public:
	Parser(const std::vector<Token> &tokens) : tokens(tokens), pos(0) {}

	double parseExpressions();
	double parseTerm();
	//Place tokens into tokens vector
	void getTokens(std::vector<Token> tokens);
	//Look at next token
	Token peek();
	//Move to next token
	Token next();
};
#endif
