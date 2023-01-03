#include "parser.h"

extern std::map<std::string, TokenType> reserved_words;

double Parser::parseExpressions()
{
	double value = parseTerm();
	while (true) {
		//char operation = peek().op;
	}
	return 0.0;
}

double Parser::parseTerm()
{
	return 0.0;
}

void Parser::getTokens(std::vector<Token> tokens) {
}

Token Parser::peek() {
	return tokens[pos];
}

Token Parser::next() {
	return tokens[pos++];
}