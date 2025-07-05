#include <stdexcept>
#include <vector>
#include <string>

class Var {
public:
	std::string name;
	double value;
	Var(std::string n, double val) : name(n), value(val) {};
};

inline std::vector<Var> var_table;

inline double get_value(std::string s) {
    for (const Var &v : var_table)
        if (v.name == s)
            return v.value;
    throw std::runtime_error("trying to read undefined variable ");
}

inline void set_value(std::string s, double val) {
    for (Var &v : var_table)
        if (v.name == s) {
            v.value = val;
			return;
		}
    throw std::runtime_error("trying to read undefined variable ");
}

inline bool is_declared(std::string name) {
	for (Var v : var_table) {
		if (v.name == name)
			return true;
	}
	return false;
}

inline double define_name(std::string name, double val) {
	if (is_declared(name)) throw std::runtime_error("declaring variable more than once");
	var_table.push_back(Var(name, val));
	return val;
}
