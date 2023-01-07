#include "parser.h"

extern std::map<std::string, TokenType> reserved_words;

int AST::type()
{
	return type_;
}

AST* AST::left()
{
	return left_;
}

AST* AST::right()
{
	return right_;
}

void AST::set_left(AST* left)
{
	left_ = left;
}

void AST::set_right(AST* right)
{
	right_ = right;
}

std::deque<Token> AST::parse(const std::vector<Token>& tokens)
{
	std::deque<Token> output_queue;
	std::vector<Token> operator_stack;

	for (const Token& token : tokens) {
		if (token.type == INTEGER) {
			output_queue.push_back(token);
		}
		else if (token.type == PLUS || token.type == MINUS || token.type == MUL || token.type == DIV) {
			const auto o1 = token;

			while (!operator_stack.empty()) {
				const auto o2 = operator_stack.back();

				if (o1.precedence <= o2.precedence) {
					operator_stack.pop_back();
					output_queue.push_back(o2);
					continue;
				}
				break;
			}
			operator_stack.push_back(o1);
		}
		else if (token.type == LEFTPARENTHESIS) {
			operator_stack.push_back(token);
		}
		else if (token.type == RIGHTPARENTHESIS) {
			bool match = false;

			while (!operator_stack.empty() && operator_stack.back().type != LEFTPARENTHESIS) {
				output_queue.push_back(operator_stack.back());
				operator_stack.pop_back();
				match = true;
			}
			if (!match && operator_stack.empty()) {
				std::cout << "Right Parenthesis Error" << std::endl;
				return {};
			}
			operator_stack.pop_back();
		}
	}

	while (!operator_stack.empty()) {
		if (operator_stack.back().type == LEFTPARENTHESIS) {
			std::cout << "Left Parenthesis Error" << std::endl;
			return {};
		}
		output_queue.push_back(std::move(operator_stack.back()));
		operator_stack.pop_back();
	}

	print(output_queue);
	return output_queue;
}

void AST::print(std::deque<Token> queue)
{
	for (int i = 0; i < queue.size(); i++) {
		if (queue[i].type == INTEGER) {
			std::cout << queue[i].int_value << std::endl;
		}
		else {
			std::cout << queue[i].string_value << std::endl;
		}
	}
}
