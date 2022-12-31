#ifndef LEXER_H
#define LEXER_H
#pragma once
#include <map>
#include <string>

// Token types
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

// Token class
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

// Lexer class
class Lexer {
private:
    std::string text;
    int pos;
    char current_char;

public:
    Lexer(std::string text) : text(text), pos(0) {
        current_char = text[pos];
    }

    void advance() {
        pos++;
        if (pos > text.length() - 1) {
            current_char = 0;
        }
        else {
            current_char = text[pos];
        }
    }

    void skip_whitespace() {
        while (current_char != 0 && isspace(current_char)) {
            advance();
        }
    }

    int integer() {
        std::string result;
        while (current_char != 0 && isdigit(current_char)) {
            result += current_char;
            advance();
        }
        return std::stoi(result);
    }

    Token get_next_token() {
        std::string word;
        std::string EOF_Str = "End of File";
        while (current_char != 0) {
            if (isspace(current_char)) {
                skip_whitespace();
                continue;
            }

            if (isdigit(current_char)) {
                return Token(INTEGER, integer());
            }

            if (isalpha(current_char) || current_char == '+' || current_char == '-' || current_char == '/' || current_char == '*' || current_char == '(' || current_char == ')' || current_char == ';') {
                word += current_char;
                advance();
            }

            if (reserved_words.count(word) > 0) {
                auto iter = reserved_words.find(word);
                return Token(iter->second, iter->first);
            }
            //throw std::invalid_argument("Invalid character");
        }

        return Token(EOFile, EOF_Str);
    }
};

#endif //LEXER_H