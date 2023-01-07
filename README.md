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

## [Code Generation Stage](https://github.com/Shivar-J/LearningCompilers/tree/CodeGeneration)
Uses both tokens and postfix equation from previous stage to create intermediate assembly code.
