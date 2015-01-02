#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
 
int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    // give "true" 1/4 of the time
    // give "false" 3/4 of the time
    std::bernoulli_distribution d(0.25);
 
    std::map<bool, int> hist;
    for(int n=0; n<10000; ++n) {
        ++hist[d(gen)];
    }
    for(auto p : hist) {
        std::cout << std::boolalpha << std::setw(5) << p.first
                  << ' ' << std::string(p.second/500, '*') << '\n';
    }
}
