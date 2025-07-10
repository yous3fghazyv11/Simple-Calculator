#include "parser.h"
#include "token.h"
#include "utils.h"
#include "var.h"
#include <cmath>
#include <stdexcept>

double statement(Token_stream &ts)
/*
 * Statement:
 *   declaration
 *   Expression
 */
{
    Token next = ts.get();
    if (next.kind == Kind::dec) {
        return declaration(ts);
    } else {
        ts.putback(next);
        return expression(ts);
    }
}

double declaration(Token_stream &ts)
/*
 * Declaration:
 *   let name = Expression
 */
{
    Token next = ts.get();
    if (next.kind != Kind::name)
        throw std::runtime_error("expceted a name");
    if (ts.get().kind != Kind::eq)
        throw std::runtime_error("expected '='");
    return define_var(next.name, expression(ts));
}

double expression(Token_stream &ts)
/*
 * Expression:
 *   Term
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
 *   Primary
 *   Primary * Primary*
 *   Primary / Primary*
 *   Primary % Primary*
 *   Primary ^ Primary
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
            case Kind::pow:
                return std::pow(left, primary(ts));
            default:
                ts.putback(next);
                return left;
        }
    }
}

double primary(Token_stream &ts)
/*
 * Primary:
 *   Value
 *   Value!
 *   +Value
 *   -Value
 *   (Expression)
 *   (Expression)!
 */
{
    Token next = ts.get();
    switch (next.kind) {
        case Kind::obrace: {
            double inside = expression(ts);
            next = ts.get();
            if (next.kind != Kind::cbrace)
                throw std::runtime_error("')' expected");
            next = ts.get();
            if (next.kind == Kind::fac) {
                if (std::floor(inside) != inside) {
                    throw std::runtime_error("factorial of non-integer not allowed");
                }
                return factorial(inside);
            }
            else
                ts.putback(next);
            return inside;
        }
        case Kind::pls:
            return value(ts);
        case Kind::mins:
            return -1 * value(ts);
        default: {
            ts.putback(next);
            double num = value(ts);
            next = ts.get();
            if (next.kind == Kind::fac) {
                if (std::floor(num) != num) {
                    throw std::runtime_error("factorial of non-integer not allowed");
                }
                return factorial(num);
            }
            ts.putback(next);
            return num;
        }
    }
}

double value(Token_stream &ts)
/*
 * Value:
 *   floating-point-value
 *   varibale name
 */
{
    Token next = ts.get();
    switch (next.kind) {
        case Kind::name:
            return get_value(next.name);
        case Kind::num:
            return next.value;
        default:
            throw std::runtime_error("invalid expression");
    }
}
