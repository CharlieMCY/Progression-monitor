#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <fstream>

using namespace std;

int main()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(20, 25);
    uniform_int_distribution<> d(10, 15);
    int num;
 
    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    for(int i = 1; i <= 200; i++) {
        int length = dis(gen);
        string filename("trace");
        filename += to_string(i);
        filename += ".txt";
        ofstream trace_file(filename.c_str());
        for(int j = 1; j <= length; j++) {
            trace_file << d(gen);
            trace_file << "\n";
        }
    }
 
}
