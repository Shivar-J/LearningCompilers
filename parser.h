#ifndef PARSER_H
#define PARSER_H
#pragma once
#include <vector>
#include <stack>
#include <iostream>
#include <queue>
#include "lexer.h"

extern std::map<std::string, TokenType> reserved_words;

//Abstract Syntax Tree Class
class AST {
private:
	int type_ = -1;
	int int_value = 0;
	char char_value = '\0';
	std::string string_value = "";
	AST* left_ = nullptr;
	AST* right_ = nullptr;
	std::vector<Token> tokens = {};
	int pos = 0;

public:
	AST(const std::vector<Token> &tokens) :tokens(tokens), pos(0) {}
	AST(int type, int value) : type_(type), int_value(value), char_value('\0'), string_value("") {}
	AST(int type, char value) : type_(type), int_value(0), char_value(value), string_value("") {}
	AST(int type, std::string value) : type_(type), int_value(0), char_value('\0'), string_value(value) {}

	int type();
	AST* left();
	AST* right();
	void set_left(AST* left);
	void set_right(AST* right);
	std::deque<Token> parse(const std::vector<Token>& tokens);
	void print(std::deque<Token> queue);
};
#endif
