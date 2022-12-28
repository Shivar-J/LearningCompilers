# LearningCompilers
Documenting my progress learning and potentially creating a compiler

## [https://github.com/Shivar-J/LearningCompilers/tree/LexicalAnalyzer](Lexical Analyzer) Stage
Tokenizes text from a file based on set token types and reserved words. Currently the amount of types are limited but I hope to increase the amount of reserved words and types allowed in the future.

## Example Testcase
```
if(2 + 2 - 1)
else(3 - 2 + 1)
```

#### Explanation of Example Testcase

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
