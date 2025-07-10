#include "token.h"
#include <stdexcept>
#include <string>

void Token_stream::putback(Token t) {
    if (full)
        throw std::runtime_error("putback into full buffer");
    buffer = t;
    full = true;
}

Token Token_stream::get() {
    if (full) {
        full = false;
        return buffer;
    }
    char current_token;
    in >> current_token;
    if (in.eof()) { // stream ended
        return Token(Kind::eoe); // signal eoe, check for it in main
    }
    switch (current_token) {
        case '+':
            return Token(Kind::pls);
        case '-':
            return Token(Kind::mins);
        case '*':
            return Token(Kind::mul);
        case '/':
            return Token(Kind::div);
        case '(':
            return Token(Kind::obrace);
        case ')':
            return Token(Kind::cbrace);
        case '!':
            return Token(Kind::fac);
        case 'q':
            return Token(Kind::quit);
        case '0': // case of a digit
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.': {
            in.putback(current_token); // put back the character
            double val;
            in >> val; // try to read a double
            return Token(Kind::num, val);
        }
        default:
            throw std::runtime_error("'" + std::string(1, current_token) + "' is undefined");
    }
}
