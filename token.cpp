#include "token.h"
#include <cctype>
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
    char ch;
    in >> ch;
    if (in.eof()) {              // stream ended
        return Token(Kind::eoe); // signal eoe, check for it in main
    }
    if (ch == '+') return Token(Kind::pls);
    if (ch == '-') return Token(Kind::mins);
    if (ch == '*') return Token(Kind::mul);
    if (ch == '/') return Token(Kind::div);
    if (ch == '^') return Token(Kind::pow);
    if (ch == '(') return Token(Kind::obrace);
    if (ch == ')') return Token(Kind::cbrace);
    if (ch == '!') return Token(Kind::fac);
    if (ch == '%') return Token(Kind::mod);
    if (ch == 'q') return Token(Kind::quit);
    if (ch == '=') return Token(Kind::eq);
    if (isdigit(ch) || ch == '.') { // case of a digit
        in.putback(ch);             // put back the character
        double val;
        in >> val; // try to read a double
        return Token(Kind::num, val);
    }
    std::string name;
    if (std::isalpha(static_cast<unsigned char>(ch))) { // case of a name
        name += ch;
        while (std::isalpha(static_cast<unsigned char>(in.peek()))) {
            in.get(ch);
            name += ch;
        }
        if (name == "let")
            return Token(Kind::dec);
        return Token(Kind::name, name);
    }
    throw std::runtime_error("bad token: " + std::string(1, ch));
}
