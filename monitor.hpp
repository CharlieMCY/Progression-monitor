#ifndef MONITOR_HPP
#define MONITOR_HPP
#include <set>
#include <string>
#include <cstring>
#include <stack>
#include <vector>

class Monitor {

 public:
    std::set<char> atomic_prop;
    std::string formula;
    int decision;
    std::stack<std::string> current_stack;
    std::stack<std::string> next_stack;
    std::stack<std::string> temp_next_stack;

    void set_params(std::string form, int d);
    int evaluate(char event);
    int reset(std::string formula);
    int rewrite(std::string current, char event);

};

#endif // MONITOR_HPP
