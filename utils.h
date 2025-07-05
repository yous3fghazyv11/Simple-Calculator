#include <iostream>
#include <fstream>
#include <stdexcept>

inline double fac(double n) {
    if (n < 0)
        throw std::runtime_error("factorial of negative");
    double result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

inline void help() { // prints help from file dec.txt
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
