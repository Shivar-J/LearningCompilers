#include <iostream>
#include <fstream>
#include "lexer.h"

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
    std::ifstream file(path);
    if(file.fail()) {
        std::cout << "Failed to open file!" << std::endl;
        return 0;
    }
    //IMPLEMENT: ignore eof for multiple lines
    std::string input;
    while(std::getline(file, input)) {
        Lexer lexer(input);
        
        while (true) {
            Token token = lexer.get_next_token();
            if (token.type == INTEGER) {
                std::cout << "Type: " << token.type << ", Value: " << token.int_value << std::endl;
            }
            if (token.type == IDENTIFIER || token.type == OPERATOR || token.type == IF || token.type == ELSE || token.type == WHILE || token.type == FOR || token.type == RETURN || token.type == PLUS || token.type == MINUS || token.type == MUL || token.type == DIV || token.type == STARTPARENTHESIS || token.type == ENDPARENTHESIS) {
                std::cout << "Type: " << token.type << ", Value: " << token.string_value << std::endl;
            }
            if (token.type == EOFile) {
                std::cout << "Type: " << token.type << ", Value: " << token.string_value << std::endl;
                break;
            }
        }
    }
    return 0;
}
