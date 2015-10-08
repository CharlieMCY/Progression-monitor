#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>

#define NUM_DAYS 60
#define NUM_USERS 23

using namespace std;

int main() {
    int trace_num = 1;
    for(int day = 1; day <= NUM_DAYS; day ++)
    {
        for(int user = 3; user <= NUM_USERS; user++)
        {
            int filenum = (user*100) + day;
            string trace(to_string(filenum));
            trace += ".txt";
            ifstream trace_file(trace.c_str());
            if(!trace_file.fail()) {
                string filename("trace");
                filename += to_string(trace_num);
                filename += ".txt";
                ofstream output(filename.c_str());
                string box;
                while(trace_file >> box) {
                    size_t pos = box.find(',');
                    box = box.substr(pos+1);
                    output << box;
                    output << "\n";
                }
                trace_num++;
                output.close();
            }
            trace_file.close();
        }
    }
}
