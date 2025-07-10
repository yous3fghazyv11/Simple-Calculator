#pragma once

#include <iostream>
#include <istream>

enum class Kind {
    num,
    pls = '+',
    mins = '-',
    mul = '*',
    div = '/',
    pow = '^',
    obrace = '(',
    cbrace = ')',
    quit = 'q',
    fac = '!',
    mod = '%',
    eoe // eoe means end of expression
    // signaled by Token_stream::get() and used in main to check garbage after an expression
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
    std::istream &in;      // a token stream tokenizes an input stream
    Token get();           // get a token from the stream
    void putback(Token t); // put a token back
    Token_stream(std::istream &s) : in(s), buffer(Kind::quit), full(false) {}

  private:
    Token buffer;
    bool full;
};
