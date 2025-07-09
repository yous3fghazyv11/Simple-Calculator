#pragma once

#include <istream>
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
