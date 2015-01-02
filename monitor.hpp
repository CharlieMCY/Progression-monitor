#ifndef MONITOR_HPP
#define MONITOR_HPP
#include <set>
#include <string>
#include <cstring>
#include <stack>
#include <vector>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <iterator>

class Monitor {

 public:
    std::set<char> atomic_prop;
    std::string formula;
    std::string antecedent;
    std::string consequent;
    std::string finally;
    std::string last;
    int decision;
    int progression;
    int ant_satisfied;
    int count;
    std::stack<std::string> current_stack;
    std::stack<std::string> next_stack;
    std::stack<std::string> temp_next_stack;
    Monitor* next;

    void set_params(std::string form, int d);
    int evaluate(char event);
    int reset();
    int rewrite(std::string& current, char event);
    int progress(char event);

};

#endif // MONITOR_HPP
