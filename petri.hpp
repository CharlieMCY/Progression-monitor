#ifndef PETRI_HPP
#define PETRI_HPP

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
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include "monitor.hpp"

// Monitor decisions:
// 1 = true
// -1 = false
// 0 = ?

class PetriNet {

 public:
    std::vector<Monitor*> petri_net;
    std::vector<std::string> cosafety_props;
    int num_traces;
    int final_decision;
	std::ofstream output;

    void create_monitor();
    int evaluate_decision();
    void read_file();
    int reset();
    int run_monitor();
    int count_monitors();

};

#endif // PETRI_HPP
