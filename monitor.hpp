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


extern int num_monitors;
extern int num_violations;
extern int max_length;

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
    int num_monitors;
    std::stack<std::string> current_stack;
    std::stack<std::string> next_stack;
    std::stack<std::string> temp_next_stack;
    Monitor* next;

    void set_params(std::string form, int d);
    int evaluate(std::string event);
    int equals(Monitor* head);
    int reset();
    int rewrite(std::string& current, std::string event);
    int progress(std::string event);

};

#endif // MONITOR_HPP
