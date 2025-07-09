#pragma once

#include <istream>
#include <stdexcept>
#include <iostream>

enum class Kind {
    num,
    pls = '+',
    mins = '-',
    mul = '*',
    div = '/',
    obrace = '(',
    cbrace = ')',
    quit = 'q',
    eoe
};

class Token {
  public:
    Kind kind;
    double value; // used only if kind == Kind::number
    Token(Kind k) : kind(k), value(0) {}
    Token(Kind k, double val) : kind(k), value(val) {}
};

class Token_stream {
  public:
    std::istream& in;
    Token get();
    void putback(Token t);
    Token_stream(std::istream& s) : in(s), buffer(Kind::quit), full(false) {}

  private:
    Token buffer;
    bool full;
};

inline void Token_stream::putback(Token t) {
    if (full)
        throw std::runtime_error("putback into full buffer");
    buffer = t;
    full = true;
}

inline Token Token_stream::get() {
    if (full) {
        full = false;
        return buffer;
    }
    char current_token;
    in >> current_token;
    if (in.eof()) {
        return Token(Kind::eoe);
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
        case 'q':
            return Token(Kind::quit);
        case '0':
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
            in.putback(current_token);
            double val;
            in >> val;
            return Token(Kind::num, val);
        }
        default:
            throw std::runtime_error("bad token");
    }
}
