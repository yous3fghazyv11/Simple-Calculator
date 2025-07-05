#include <fstream>
#include <iostream>
#include <stdexcept>
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
    num
};

class Token {
  public:
    Token_kind kind;
    double value;
    Token(Token_kind k) : kind(k), value(0) {};
    Token(Token_kind k, double val) : kind(k), value(val) {};
};

class Token_stream {
  public:
    void putback(Token t);
    Token get();
    void ignore(Token_kind k);
    Token_stream() : full{false}, buffer{Token_kind::print} {}

  private:
    bool full = false;
    Token buffer;
};

extern Token_stream ts;

inline void Token_stream::putback(Token t) {
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
        case '+': return Token(Token_kind::plus);
        case '-': return Token(Token_kind::mins);
        case '*': return Token(Token_kind::mul);
        case '/': return Token(Token_kind::div);
        case 'q': return Token(Token_kind::quit);
        case ';': return Token(Token_kind::print);
        case '(': return Token(Token_kind::obrace);
        case ')': return Token(Token_kind::cbrace);
        case '!': return Token(Token_kind::fac);
        case '^': return Token(Token_kind::pow);
        case 'h': return Token(Token_kind::help);
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
            std::cin.putback(current_token);
            double val = 0;
            std::cin >> val;
            return Token(Token_kind::num, val);
        }
        default:
            throw std::runtime_error("'" + std::string(1, current_token) +
                                     "' unrecognized token");
    }
}

inline double fac(double n) {
    if (n < 0)
        throw std::runtime_error("factorial of negative");
    double result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

inline void help() {
    std::ifstream in{"doc.txt", std::ios::binary};
    if (!in) {
        std::cerr << "cannot open doc.txt\n";
        return;
    }
    constexpr std::size_t buf_sz = 4096;
    char buffer[buf_sz];
    while (in.read(buffer, buf_sz) || in.gcount()) {
        std::cout.write(buffer, in.gcount());
    }
}
