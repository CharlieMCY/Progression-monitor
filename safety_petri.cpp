#include "petri.hpp"

using namespace std;

void PetriNet::read_file() {

    string formula;
    ifstream input("input.txt");
    input >> num_traces;
    while(input >> formula) {
        output<<"Formula "<<formula<<endl;
        Monitor* new_monitor = new Monitor();
        new_monitor->set_params(formula, 0);
        petri_net.push_back(new_monitor);
        cosafety_props.push_back(formula);
        num_monitors++;
    }
    input.close();
}

void PetriNet::create_monitor() {

	output.open("output.txt");
    this->read_file();
    this->final_decision = 0;
    this->run_monitor();
    output<<"Maximum length of formula monitored: "<<max_length<<endl;
    output<<"Number of violations: "<<num_violations<<endl;

}

int PetriNet::count_monitors() {
    int count = 0;
    vector<Monitor*>::iterator it_mon = petri_net.begin();
    while(it_mon != petri_net.end())
    {
        Monitor* current_mon = *it_mon;
        while(current_mon != NULL) {
            count++;
            current_mon = current_mon->next;
        }
        it_mon++;
    }
    return count;
}

int PetriNet::run_monitor() {
    for(int i = 1; i <= num_traces; i++) {
        string filename = "trace";
        filename += to_string(i);
        filename += ".txt";
        ifstream trace_file(filename.c_str());
        output<<"Reading trace file: "<<filename<<endl;
        string event;
        if(!trace_file.fail()) {
            while(trace_file >> event && !petri_net.empty()) {
                //output<<event<<endl;
                vector<Monitor*>::iterator it_mon = petri_net.begin();
                while(it_mon != petri_net.end())
                {
                    Monitor* current_mon = *it_mon;
                    int erased = 0;
                    while(current_mon != NULL) {
                        if(current_mon->decision == 0) {
                            int result = current_mon->evaluate(event);
                            //output<<"Result "<<result<<endl;
                            if(result == -1) {
                                it_mon = petri_net.erase(it_mon);
                                int index = distance(petri_net.begin(), it_mon);
                                cosafety_props.erase(cosafety_props.begin() + index);
                                erased = 1;
                                break;
                            }
                        }
                        current_mon = current_mon->next;
                    }
                    if(erased == 0) {
                        it_mon++;
                    }
                }
            }
            if(evaluate_decision() == -1) {
                final_decision = -1;
                output<<"Property violated"<<endl;
                num_violations++;
                output<<"Number of monitors created: "<<count_monitors()<<endl;
                return 1;
            }
            //output<<"reseting petri"<<endl;
            this->reset();
        }
    }
    final_decision = 0;
    output<<"Property unknown"<<endl;
    output<<"Number of monitors created: "<<count_monitors()<<endl;
    return 1;
}

int PetriNet::evaluate_decision() {
    if(petri_net.empty())
        return -1;
    for(vector<Monitor*>::iterator it_mon = petri_net.begin(); it_mon != petri_net.end(); it_mon++) {
        Monitor* current_mon = *it_mon;
        while(current_mon != NULL) {
            if((current_mon->progression <= 0) && current_mon->decision <= 0)
                return -1;
            current_mon = current_mon->next;
        }
    }
    return 1;
}

int PetriNet::reset() {
    for(int i = 0; i < petri_net.size(); i++) {
        petri_net[i]->reset();
    }
    return 1;
}
