#include "petri.hpp"

using namespace std;

void PetriNet::read_file() {

    string formula;
    ifstream input("input.txt");
    input >> num_traces;
    while(input >> formula) {
        cout<<formula<<endl;
        Monitor* new_monitor = new Monitor();
        new_monitor->set_params(formula, 0);
        petri_net.push_back(new_monitor);
        cosafety_props.push_back(formula);
    }
    input.close();
}

void PetriNet::create_monitor() {

    this->read_file();
    this->final_decision = 0;
    this->run_monitor();
}

int PetriNet::run_monitor() {

    for(int i = 1; i <= num_traces; i++) {
        string filename = "trace";
        filename += (char)(((int)'0')+i);
        filename += ".txt";
        ifstream trace_file(filename.c_str());
        char event;
        while(trace_file >> event && !petri_net.empty()) {
            cout<<event<<endl;
            vector<Monitor*>::iterator it_mon = petri_net.begin();
            while(it_mon != petri_net.end())
            {
                Monitor* current_mon = *it_mon;
                int erased = 0;
                while(current_mon != NULL) {
                    if(current_mon->decision == 0) {
                        int result = current_mon->evaluate(event);
                        cout<<"Result "<<result<<endl;
                        if(result == 1) {
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
            cout<<"Property violated"<<endl;
            return 1;
        }
        this->reset();
    }
    return 1;
}

int PetriNet::evaluate_decision() {
    if(petri_net.empty())
        return -1;
    //for(vector<Monitor*>::iterator it_mon = petri_net.begin(); it_mon != petri_net.end(); it_mon++) {
    //    Monitor* current_mon = *it_mon;
    //    while(current_mon != NULL) {
    //    if(((*it_mon)->progression <= 0) && (*it_mon)->decision <= 0)
    //        return 0;
    //}
    return -1;
}

int PetriNet::reset() {
    for(int i = 0; i < petri_net.size(); i++) {
        petri_net[i]->reset();
    }
    return 1;
}
