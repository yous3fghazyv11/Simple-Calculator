#include "var.h"
#include <stdexcept>

std::vector<Var> var_table;

double get_value(std::string s) {
    for (Var v : var_table) {
        if (v.name == s)
            return v.value;
    }
    throw std::runtime_error("undefined variable: " + s);
}

// double set_value(std::string s, double val) {
//     for (Var v : var_table) {
//         if (v.name == s)
//             v.value = val;
//     }
//     throw std::runtime_error("undefined variable: " + s);
// }

double define_var(std::string name, double val) {
    var_table.push_back(Var(name, val));
    return val;
}
