#include "parser.h"
#include "utils.h"
#include <cmath>
#include <stdexcept>

double expression(Token_stream &ts)
/*
 * Expression:
 *   Term + Term*
 *   Term - Term*
 */    
{
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

double term(Token_stream &ts)
/*
 * Term:
 *   Primary * Primary*
 *   Primary / Primary*
 *   Primary % Primary*
 *   Primary ^ Primary*
 */    
{
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
            case Kind::mod: {
                double val = primary(ts);
                if (val == 0)
                    throw std::runtime_error("divison by zero");
                left = std::fmod(left, val);
                next = ts.get();
                break;
            }
            default:
                ts.putback(next);
                return left;
        }
    }
}

double primary(Token_stream &ts)
/*
 * Primary:
 *   Number
 *   Number!
 *   +Number
 *   -Number
 *   (Expression)
 *   (Expression)!
 */    
{
    Token next = ts.get();
    switch (next.kind) {
        case Kind::num: {
            Token is_fac = ts.get();
            if (is_fac.kind == Kind::fac) {
                return factorial(next.value);
            }
            ts.putback(is_fac);
            return next.value;
        }
        case Kind::pls:
            return primary(ts);
        case Kind::mins:
            return -1 * primary(ts);
        case Kind::obrace: {
            double inside = expression(ts);
            next = ts.get();
            if (next.kind != Kind::cbrace)
                throw std::runtime_error("')' expceted");
            Token is_fac = ts.get();
            if (is_fac.kind == Kind::fac) {
                return factorial(inside);
            }
            ts.putback(is_fac);
            return inside;
        }
        default:
            throw std::runtime_error("invalid epxression");
    }
}
