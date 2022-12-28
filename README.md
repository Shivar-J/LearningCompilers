# LearningCompilers
Documenting my progress learning and potentially creating a compiler

## Lexical Analyzer Phase

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
