/*
   the input loop is pretty simple
   first, we read a line from the input stream
   then we make a string stream out of that line
   then we make a Token_stream out of that string stream
   then we feed that Token_stream to out statement() function
 */

#include "parser.h"
#include "token.h"
#include "var.h"
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

#define GREEN "\033[92m"
#define RED "\033[33m"
#define WHITE "\033[0m"

void repl() {
    for (std::string line; std::cout << "> " && std::getline(std::cin, line);) { // get line from the user
        try {
            std::stringstream line_buffer{line}; // turn that line into a string stream
            Token_stream ts(line_buffer);        // turn that string stream (originally just input
                                                 // line) into a token stream
            Token t = ts.get();
            if (t.kind == Kind::quit) { // if the user types q
                break;
            }
            if (t.kind == Kind::eoe) { // if the user didn't type anything
                continue;
            }
            if (t.kind == Kind::com) { // this line is a comment
                continue;
            }
            ts.putback(t); // if none of the above then put it back to read a statement
            double result = statement(ts);
            if (ts.get().kind != Kind::eoe) { // make sure that there's no garbage after a statement
                std::cerr << RED << "invalid expression\n" << WHITE;
                continue;
            }
            set_value("ans", result);
            std::cout << GREEN << result << WHITE << '\n';
        } catch (std::exception &e) {
            std::cerr << RED << e.what() << WHITE << '\n';
        }
    }
}

void read_config() {
    std::string line;
    std::string config_path = std::string(std::getenv("HOME")) + "/.config/calc/calc";
    std::ifstream file{config_path};
    if (!file) {
        std::cerr << "can't find config file in: " << config_path << '\n';
        return;
    }
    while (std::getline(file, line)) {
        try {
            std::stringstream line_buffer{line}; // turn that line into a string stream
            Token_stream ts(line_buffer);        // turn that string stream (originally just input line) into a token stream
            Token t = ts.get();
            if (t.kind == Kind::com) { // this line is a comment
                continue;
            } else {
                ts.putback(t);
            }
            statement(ts);
            // double result = statement(ts);
            if (ts.get().kind != Kind::eoe) { // make sure that there's no garbage after the expression
                std::cerr << RED << "error in config file: " << config_path << WHITE;
                std::cerr << RED << "invalid expression: " << line << WHITE;
                continue;
            }
            // std::cout << "expression: " << line << '\n';
            // std::cout << "output: " << result << '\n';
        } catch (std::exception &e) {
            std::cerr << RED << e.what() << WHITE << '\n';
        }
    }
    std::cout << "config file read done\n";
}

int main() try {
    define_var("pi", 22.0/7);
    define_var("e", 2.71828);
    define_var("ans", 0);
    std::cout << "type 'q' or 'quit' to exit\n";
    read_config();
    repl();
    return 0;
} catch (std::exception &e) {
    std::cerr << RED << "Error: " << e.what() << WHITE << '\n';
    return 1;
} catch (...) {
    std::cerr << RED << "Unexpected error accured" << WHITE << '\n';
    return 2;
}
