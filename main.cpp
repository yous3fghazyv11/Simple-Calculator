#include "utils.h"
#include "var.h"
#include "token.h"
#include <cmath>
#include <ios>
#include <limits>
#include <stdexcept>

Token_stream ts;

double statement();
double declaration();
double expression();
double term();
double primary();

double statement() {
    Token next = ts.get(); 
    switch (next.kind) { 
    case Token_kind::let: // handels "let" keyword and executes declaration
        return declaration();
        break;
    default:
        ts.putback(next);
        return expression(); // if not "let", handle normal expression
    }
}

double declaration() { // we assume that we've already seen "let"
    Token var = ts.get();
    if (var.kind != Token_kind::name) { // after let there should come a name token
        throw std::runtime_error("expected a variable name");
    }

    Token next = ts.get();
    if (next.kind != Token_kind::equal) { // after the name there should be equal token
        throw std::runtime_error("'=' expected");
    }
    double d = expression(); // get the expression that is going to be the value of the variable
    return define_name(var.name, d);
}

double expression() {
    double left = term();
    Token next = ts.get();
    while (true) {
        switch (next.kind) {
            case Token_kind::plus: // handle +
                left += term();
                next = ts.get();
                break;
            case Token_kind::mins: // handle -
                left -= term();
                next = ts.get();
                break;
            default: // no more + or -, return left
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
            case Token_kind::mul: // handle *
                left *= primary();
                next = ts.get();
                break;
            case Token_kind::div: { // handle /
                double d = primary();
                if (d == 0) {
                    throw std::runtime_error("division by zero");
                }
                left /= d;
                next = ts.get();
                break;
            }
            case Token_kind::pow: // handle ^
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
        case Token_kind::num: { // simple number
            Token next = ts.get();
            if (next.kind == Token_kind::fac) {
                return fac(t.value);
            }
            ts.putback(next);
            return t.value;
        }
        case Token_kind::mins: // handle negative numbers
            return -1 * primary();
        case Token_kind::plus: // handle positive numbers
            return primary();
        case Token_kind::obrace: { // handle open braces
            double left = expression(); // get value of expression inside
            Token next = ts.get();
            if (next.kind != Token_kind::cbrace) { // obrace must have cbrace
                throw std::runtime_error("')' Exprected");
            }
            Token is_fac = ts.get();
            if (is_fac.kind == Token_kind::fac) { // handle factorial of expression inside braces
                return fac(left);
            }
            ts.putback(is_fac);
            return left;
        }
        case Token_kind::name: return get_value(t.name);
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
                t = ts.get();
            if (t.kind == Token_kind::quit)
                return;
            if (t.kind == Token_kind::help) {
                help();
                continue;
            }
            ts.putback(t);
            std::cout << "= " << statement() << '\n';
        } catch (std::runtime_error &e) {
            std::cerr << e.what() << '\n';
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), ';');
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
