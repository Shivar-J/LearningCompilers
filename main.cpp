#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "lexer.h"

std::string readfile(std::string name) {
    std::ifstream file(name);

    if (file.fail()) {
        std::cout << "Failed to open file!" << std::endl;
        exit(1);
    }

    std::vector<std::string> contents;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream str(line);
        std::string word;
        while (str >> word) {
            contents.push_back(word);
        }
        contents.push_back(";");
    }

    std::string content;
    for (const auto& s : contents) {
        content += s;
    }
    return content;
}

int main() {
    //EXAMPLE EXPRESSIONS: if(2 + 2 - 1);
    std::cout << "Lexical Analyzer" << "\nExample Expression: if(2 + 2 - 1)" << std::endl;
    #ifdef _WIN32
    system("explorer /select, C:\\");
    std::cout << "Drag File to CMD then press Enter: " << std::endl;
    #else
    std::cout << "Enter Path to File: " << std::endl;
    #endif
    
    std::string path;
    std::cin >> path;
    std::string contents = readfile(path);
    std::cout << contents << std::endl;
    //IMPLEMENT: count which line the code is currently on
    std::vector<Token> tokens;
    Lexer lexer(contents);
        
    while (true) {
        Token token = lexer.get_next_token();
        if (token.type == INTEGER) {
            std::cout << "Type: " << token.type << ", Value: " << token.int_value << std::endl;
            tokens.push_back(token);
        }
        if (token.type == IDENTIFIER || token.type == OPERATOR || token.type == IF || token.type == ELSE || token.type == WHILE || token.type == FOR || token.type == RETURN || token.type == PLUS || token.type == MINUS || token.type == MUL || token.type == DIV || token.type == STARTPARENTHESIS || token.type == ENDPARENTHESIS) {
            std::cout << "Type: " << token.type << ", Value: " << token.string_value << std::endl;
            tokens.push_back(token);
        }
        if (token.type == EOFile) {
            std::cout << "Type: " << token.type << ", Value: " << token.string_value << std::endl;
            tokens.push_back(token);
            break;
        }
    }
}
