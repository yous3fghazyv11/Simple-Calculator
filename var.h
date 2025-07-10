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

double get_value(const std::string& s);
void set_value(const std::string& s, double val);
double define_var(const std::string& name, double val);
bool is_defined(const std::string& name);
