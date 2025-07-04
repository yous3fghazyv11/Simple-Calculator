#include "utils.h"
#include <cmath>
#include <stdexcept>

Token_stream ts;

double expression();
double term();
double primary();

double expression() {
    double left = term();
    Token next = ts.get();
    while (true) {
        switch (next.kind) {
            case Token_kind::plus:
                left += term();
                next = ts.get();
                break;
            case Token_kind::mins:
                left -= term();
                next = ts.get();
                break;
            default:
                ts.putback(next);
                return left;
        }
    }
}

double term() {
    double left = primary();
    Token next = ts.get();
    while (true) {
        switch (next.kind) {
            case Token_kind::mul:
                left *= primary();
                next = ts.get();
                break;
            case Token_kind::div: {
                double d = primary();
                if (d == 0) {
                    throw std::runtime_error("division by zero");
                }
                left /= d;
                next = ts.get();
                break;
            }
            case Token_kind::pow:
                left = std::pow(left, primary());
                next = ts.get();
                break;
            default:
                ts.putback(next);
                return left;
        }
    }
}

double primary() {
    Token t = ts.get();
    switch (t.kind) {
        case Token_kind::num: {
            Token next = ts.get();
            if (next.kind == Token_kind::fac) {
                return fac(t.value);
            }
            ts.putback(next);
            return t.value;
        }
        case Token_kind::mins: {
            return -1 * primary();
        }
        case Token_kind::plus: {
            return primary();
        }
        case Token_kind::obrace: {
            double left = expression();
            Token next = ts.get();
            if (next.kind != Token_kind::fac) {
                throw std::runtime_error("')' Exprected");
            }
            Token is_fac = ts.get();
            if (is_fac.kind == Token_kind::fac) {
                return fac(left);
            }
            ts.putback(is_fac);
            return left;
        }
        default:
            throw std::runtime_error("primary expected");
    }
}

void calculate() {
    while (std::cin) {
        try {
            std::cout << "> ";
            Token t = ts.get();
            while (t.kind == Token_kind::print)
                // first discard all "prints"
                t = ts.get();
            if (t.kind == Token_kind::quit)
                return;
            if (t.kind == Token_kind::print) {
                help();
                continue;
            }
            ts.putback(t);
            std::cout << "= " << expression() << '\n';
        } catch (std::runtime_error &e) {
            std::cerr << e.what() << '\n';
            // ts.ignore(print);
        }
    }
}

int main() try {
    calculate();
    return 0;
} catch (std::runtime_error &e) {
    std::cerr << e.what() << '\n';
    return 1;
} catch (...) {
    std::cerr << "exception \n";
    return 2;
}
