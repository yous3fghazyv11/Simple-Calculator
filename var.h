#pragma once
#include <string>
#include <vector>

class Var{
public:
    std::string name;
    double value;
    Var(std::string n, double val) : name(n), value(val) {}
};

extern std::vector<Var> var_table;

double get_value(std::string s);
double set_value(std::string s, double val);
double define_var(std::string name, double val);
