#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string>

enum class Token_kind {
    plus,
    mins,
    mul,
    div,
    quit,
    print,
    obrace,
    cbrace,
    fac,
    pow,
    help,
    num,
	let,
	name,
	equal,
};

class Token {
  public:
    Token_kind kind;
    double value;
	std::string name;
    Token(Token_kind k) : kind(k), value(0) {};
    Token(Token_kind k, double val) : kind(k), value(val) {};
    Token(Token_kind k, std::string n) : kind(k), name(n) {};
};

class Token_stream {
  public:
    void putback(Token t);
    Token get();
    Token_stream() : full{false}, buffer{Token_kind::print} {}
  private:
    bool full = false;
    Token buffer;
};

extern Token_stream ts;

inline void Token_stream::putback(Token t) {
	if (full) {
		throw std::runtime_error("putback into full buffer");
	}
    buffer = t;
    full = true;
}

inline Token Token_stream::get() {
    if (full) {
        full = false;
        return buffer;
    }
    char current_token = '\0';
    std::cin >> current_token;
    if (!std::cin) {
        std::cout << "\nExiting...\n";
        exit(0);
    }
    switch (current_token) {
        case '+':
            return Token(Token_kind::plus);
        case '-':
            return Token(Token_kind::mins);
        case '*':
            return Token(Token_kind::mul);
        case '/':
            return Token(Token_kind::div);
        case 'q':
            return Token(Token_kind::quit);
        case ';':
            return Token(Token_kind::print);
        case '(':
            return Token(Token_kind::obrace);
        case ')':
            return Token(Token_kind::cbrace);
        case '!':
            return Token(Token_kind::fac);
        case '^':
            return Token(Token_kind::pow);
        case 'h':
            return Token(Token_kind::help);
        case '=':
            return Token(Token_kind::equal);
		case '0': // case of number literal
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
            std::cin.putback(current_token); // putback the number
            double val = 0;
            std::cin >> val; // read a full double
            return Token(Token_kind::num, val);
        }
		default:
			if (std::isalpha(current_token)) { // is it a character?
				std::cin.putback(current_token);
				std::string s;
				char ch;
				while (std::cin.get(ch) && (isalpha(ch) || isdigit(ch))) // read a string of characters
					s+=ch;
				if (s == "let") { // is it let?
					return Token(Token_kind::let);
				}
				return Token(Token_kind::name, s); // then must be a name
			}
            throw std::runtime_error("'" + std::string(1, current_token) +
                                     "' unrecognized token");
    }
}

