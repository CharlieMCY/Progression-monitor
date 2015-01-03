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
    uniform_int_distribution<> dis(30, 50);
    normal_distribution<> d(50,4);
    int num;
 
    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    for(int i = 1; i <= 1; i++) {
        int length = dis(gen);
        string filename("trace");
        filename += (char)(((int)'0')+i);
        filename += ".txt";
        ofstream trace_file(filename.c_str());
        for(int j = 1; j <= length; j++) {
            num = round(d(gen));
            trace_file << num;
            trace_file << "\n";
        }
    }
 
}
