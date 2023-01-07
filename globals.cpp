#include <map>
#include <string>

enum TokenType {
    INTEGER,
    PLUS,
    MINUS,
    MUL,
    DIV,
    EOFile,
    IF,
    ELSE,
    WHILE,
    FOR,
    RETURN,
    IDENTIFIER,
    OPERATOR,
    STARTPARENTHESIS,
    ENDPARENTHESIS,
    NEWLINE,
};

std::map<std::string, TokenType> reserved_words = {
    {"if", IF},
    {"else", ELSE},
    {"while", WHILE},
    {"for", FOR},
    {"return", RETURN},
    {"+", PLUS},
    {"-", MINUS},
    {"*", MUL},
    {"/", DIV},
    {"(", STARTPARENTHESIS},
    {")", ENDPARENTHESIS},
    {";", NEWLINE},
};