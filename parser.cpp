#include "parser.h"
#include <stdexcept>

double expression(Token_stream &ts) {
    double left = term(ts);
    Token next = ts.get();
    while (true) {
        switch (next.kind) {
            case Kind::pls:
                left += term(ts);
                next = ts.get();
                break;
            case Kind::mins:
                left -= term(ts);
                next = ts.get();
                break;
            default:
                ts.putback(next);
                return left;
        }
    }
}

double term(Token_stream &ts) {
    double left = primary(ts);
    Token next = ts.get();
    while (true) {
        switch (next.kind) {
            case Kind::mul:
                left *= primary(ts);
                next = ts.get();
                break;
            case Kind::div: {
                double val = primary(ts);
                if (val == 0)
                    throw std::runtime_error("divison by zero");
                left /= val;
                next = ts.get();
                break;
            }
            default:
                ts.putback(next);
                return left;
        }
    }
}

double primary(Token_stream &ts) {
    Token next = ts.get();
    switch (next.kind) {
        case Kind::num:
            return next.value;
        case Kind::obrace: {
            double left = expression(ts);
            next = ts.get();
            if (next.kind != Kind::cbrace) {
                throw std::runtime_error("')' expceted");
            }
            return left;
        }
        default:
            throw std::runtime_error("invalid epxression");
    }
}
