/*
   the input loop is pretty simple
   first, we read a line from the input stream
   then we make a string stream out of that line
   then we make a Token_stream out of that string stream
   then we feed that Token_stream to out expression() function
 */

#include "parser.h"
#include "token.h"
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

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
            ts.putback(t); // if none of the above then put it back to read an
                           // expression
            double result = expression(ts);
            if (ts.get().kind != Kind::eoe) { // make sure that there's no
                                              // garbage after the expression
                std::cerr << RED << "invalid expression\n" << WHITE;
                continue;
            }
            std::cout << GREEN << result << WHITE << '\n';
        } catch (std::exception &e) {
            std::cerr << RED << e.what() << WHITE << '\n';
        }
    }
}

void read_from_file(char *name) {
    std::string line;
    std::ifstream file{name};
    if (!file) {
        throw std::runtime_error("can't open file: " + std::string(name));
    }
    while (std::getline(file, line)) {
        try {
            std::cout << '\n' << line << '\n';
            std::stringstream line_buffer{line}; // turn that line into a string stream
            Token_stream ts(line_buffer);        // turn that string stream (originally just input line) into a token stream
            Token t = ts.get();
            if (t.kind == Kind::quit) { // if the user types q
                break;
            }
            if (t.kind == Kind::eoe) { // if the user didn't type anything
                continue;
            }
            ts.putback(t); // if none of the above then put it back to read an expression
            double result = expression(ts);
            if (ts.get().kind != Kind::eoe) { // make sure that there's no garbage after the expression
                std::cerr << RED << "invalid expression\n" << WHITE;
                continue;
            }
            std::cout << GREEN << result << WHITE << '\n';
        } catch (std::exception &e) {
            std::cerr << RED << e.what() << WHITE << '\n';
        }
    }
}

int main(int argc, char *argv[]) try {
    if (argc == 1) {
        repl();
    } else if (argc == 2) {
        read_from_file(argv[1]);
    } else {
        throw std::runtime_error("can only read from one file at a time");
    }
    return 0;
} catch (std::exception &e) {
    std::cerr << RED << "Error: " << e.what() << WHITE << '\n';
    return 1;
} catch (...) {
    std::cerr << RED << "Unexpected error accured" << WHITE << '\n';
    return 2;
}
