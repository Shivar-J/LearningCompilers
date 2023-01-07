# LearningCompilers
Documenting my progress learning and potentially creating a compiler

## [Lexical Analysis Stage](https://github.com/Shivar-J/LearningCompilers/tree/LexicalAnalyzer)
Tokenizes text from a file based on set token types and reserved words. Currently the amount of types are limited but I hope to increase the amount of reserved words and types allowed in the future.

## Example Testcase
```
if(2 + 2) * (4 / 2)
```

#### Explanation of Example Testcase
```
Reserved Words within testcase: if, (, +, -, )
2, 2, and 1 are identified as integers

Console prints:
Type: 6, Value: if, Precedence: 0
Type: 13, Value: (, Precedence: 0
Type: 0, Value: 2, Precedence: 0
Type: 1, Value: +, Precedence: 1
Type: 0, Value: 2, Precedence: 0
Type: 14, Value: ), Precedence: 0
Type: 3, Value: *, Precedence: 2
Type: 13, Value: (, Precedence: 0
Type: 0, Value: 4, Precedence: 0
Type: 4, Value: /, Precedence: 2
Type: 0, Value: 2, Precedence: 0
Type: 14, Value: ), Precedence: 0
Type: 5, Value: End of File, Precedence: -1

Precedence is 0 for anything other than mathematical operators right now. Can be inproved by grouping curly bracket code(ie. runs code in curly brackets first).
Both + and - have a precedence value of 1 because when following order of operations (BEDMAS/PEMDAS), addition and subtraction have the same priority.
End of file has a precedence of -1 because it can't be 0 or greater than 1.
Type values are assigned based on a enum class containing all currently valid types.
In the future, I can improve this code by adding support for more types and a better precedence system.
```

### Code Snippet
```cpp
class Token {
public:
    TokenType type;
    int int_value;
    std::string string_value;
    char char_value;

    Token(TokenType type, int value) : type(type), int_value(value), string_value(""), char_value(' ') {}
    Token(TokenType type, std::string value) : type(type), int_value(0), string_value(value), char_value(' ') {}
    Token(TokenType type, char value) : type(type), int_value(0), string_value(""), char_value(value) {}
};
```

## [Syntax Analysis Stage](https://github.com/Shivar-J/LearningCompilers/tree/SyntaxAnalysis)
Parses the relevant tokens and performs operations based on that token type. Currently limited to the same types as in the "lexical analysis" stage. Uses the Shunting-Yard algorithm to convert tokens to postfix notation

### Code Snippet (Shunting-Yard Algorithm)
```cpp
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
```
The Shunting Yard algorithm is used to convert infix notation to postfix notation. In the code above I also handle parenthesis as I didn't handle them when I assigned a precedence value to each token in the first stage. The code uses a stack and a queue to hold operators and operands respectfully then merge them both at the end. The end results in a expression such as 4 2 + (4 + 2) (*figure 2.1*) or 2 2 + 4 2 / * (*figure 2.2*). 

```
	+
      /   \
     4     2
    Figure 2.1
```

```
	*
      /   \
     +     "/"
    / \    /  \
   2   2  4    2
    Figure 2.2
```


## [Code Generation Stage](https://github.com/Shivar-J/LearningCompilers/tree/CodeGeneration)
Uses both tokens and postfix equation from previous stage to create intermediate assembly code.

### Code Snippet
```cpp
for (;;) {
	if (*s == '*') {
		s++;
		fprintf(file, "%p    push eax\n", (void*)&s);
		compileTerm(s);
		fprintf(file, "%p    mov  ebx, eax\n", (void*)&s);
		fprintf(file, "%p    pop  eax\n", (void*)&s);
		fprintf(file, "%p    imul ebx\n", (void*)&s);
	}
	else if (*s == '/') {
		s++;
		fprintf(file, "%p    push eax\n", (void*)&s);
		compileTerm(s);
		fprintf(file, "%p    mov  ebx, eax\n", (void*)&s);
		fprintf(file, "%p    pop  eax\n", (void*)&s);
		fprintf(file, "%p    idiv ebx\n", (void*)&s);
	}
	else {
		break;
	}
}
```

Currently the code generated is very inefficient and doesn't support anything but very limited math equations, but it produces a workable assembly code based on a given math equation.
