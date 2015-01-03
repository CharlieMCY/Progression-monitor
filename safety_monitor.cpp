#include "monitor.hpp"

using namespace std;

//Value of progression: -1 -> invalid, 0 -> progressed formula ready, >=1
//->progression in process
void Monitor::set_params(string form, int d) {
    if(form == "=f") {
        ifstream func("func.txt");
        this->progression = 1;
        func >> antecedent;
        func >> consequent;
        func >> last;
        this->formula = "";
        this->ant_satisfied = 0;
        this->next = NULL;
        this->count = 0;
    } else {
        this->progression = -1;
        this->formula = form;
    }
    this->decision = d;
    current_stack.push(this->formula);
}

int Monitor::evaluate(char event) {
    if(progression == -1) {
        int flag = 0, i;
        while(!current_stack.empty()) {
            cout<<"Rewriting formula: "<<current_stack.top()<<" on event "<<event<<endl;
            i = rewrite(current_stack.top(), event);
            current_stack.pop();
            if(i == 1) {
                flag = 1;
            } else if(i == -1) {
                flag = -1;
            }
            cout<<" return "<<i<<" flag "<<flag<<endl;
        }
        swap(current_stack, next_stack);
        this->decision = flag;
        return flag;
    } else if(progression == 0) {
        int flag = 1, i;
        while(!current_stack.empty()) {
            cout<<"Rewriting formula: "<<current_stack.top()<<" on event "<<event<<endl;
            i = rewrite(current_stack.top(), event);
            current_stack.pop();
            if(i == -1) {
                flag = -1;
            } else if(i == 0 && flag != -1) {
                flag = 0;
            }
            cout<<" return "<<i<<" flag "<<flag<<endl;
        }
        if(ant_satisfied == 0){
            if(flag == 1) {
                cout<<"Pushing"<<formula<<" and "<<finally<<endl;
                current_stack.push(formula);
                current_stack.push(finally);
                this->decision = 0;
                ant_satisfied = 1;
                return 0;
            } else if(flag == -1) {
                this->decision = 1;
                return 1;
            }
        }
        swap(current_stack, next_stack);
        this->decision = flag;
        return flag;
    } else {
        return progress(event);
    }

}

int Monitor::reset() {
    if(progression == -1) {
        this->decision = 0;
        while(!this->current_stack.empty()) {
            this->current_stack.pop();
        }
        this->current_stack.push(this->formula);
    } else {
        cout<<"Resetting"<<endl;
        Monitor* current_mon = this;
        while(current_mon != NULL) {
            current_mon->decision = 0;
            while(!current_mon->current_stack.empty()) {
                current_mon->current_stack.pop();
            }
            if(current_mon->progression >= 1) {
                cout<<"Ante "<<antecedent<<endl;
                current_mon->current_stack.push(current_mon->antecedent);
                current_mon->progression = 0;
                current_mon->next = new Monitor();
                current_mon->next->set_params("=f", 0);
                break;
            }
            current_mon = current_mon->next;
        }
    }
    return 1;
}

// return 0 if progression worked properly
int Monitor::progress(char event) {
    size_t pos;
    if(count == 0) {
        pos = antecedent.find('x');
        if(pos != string::npos) {
            antecedent.replace(pos, 1, &event, 1);
        }
        count++;
    }
    else {
        string current = consequent;
        pos = current.find('x');
        if(pos != string::npos) {
            current.replace(pos, 1, &event, 1);
        }
        if(formula.empty()) {
            formula.assign(current);
        } else {
            formula.insert(0, "(");
            formula.append(")&(");
            string next = "";
            for(int i = 1; i <= progression; i++) {
                next.append("X(");
            }
            next.append(current);
            for(int i = 1; i <= progression; i++) {
                next.append(")");
            }
            next.append(")");
            formula.append(next);
            cout<<"formula "<<formula<<endl;
            progression++;
        }
    }
    finally = last;
    pos = finally.find('x');
    if(pos != string::npos) {
        finally.replace(pos, 1, &event, 1);
    }
    return 0;
}

// return 0 if maybe, -1 if unstatisfied otherwise 1
int Monitor::rewrite(string& current, char event) {
    stack<char> bracs;
    char op = '\0';
    stack<string> operands;
    string curr = "";
    int i = 0;
    while(i < current.length()) {
        switch(current[i]) {
            case 'G': 
            case 'F': 
            case '~':
            case 'U':
            case '|':
            case '&':
            case 'X': op = current[i];
                      i++;
                      break;
            case '(': bracs.push('(');
                      curr.assign(&current[i], 1);
                      i++;
                      while(!bracs.empty()) {
                        if(current[i] == '(')
                            bracs.push('(');
                        else if(current[i] == ')')
                            bracs.pop();
                        curr += current[i];
                        i++;
                      }
                      operands.push(curr);
                      break;
            default: string operand(&current[i]); 
                     operands.push(operand);
                     i++;

        };
    }
    if(op == 'G') {
        string top = operands.top();
        operands.pop();
        string curr = top.substr(1, top.length()-2);
        cout<<"next rewrite on "<<curr<<endl;
        if(rewrite(curr, event) == 1) {
            string next(&op, 1);
            next += top;
            next_stack.push(next);
            return 0;
        }
        cout<<"Returning -1"<<endl;
        return -1;
    } else if(op == 'F') {
        string top = operands.top();
        operands.pop();
        string curr = top.substr(1, top.length()-2);
        if(rewrite(curr, event) <= 0) {
            string next(&op, 1);
            next += top;
            next_stack.push(next);
            return 0;
        }
        return 1;
    } else if(op == 'X') {
        string next = operands.top();
        operands.pop();
        next = next.substr(1, next.length()-2);
        next_stack.push(next);
        return 0;
    } else if(op == '~') {
        string curr = operands.top();
        operands.pop();
        curr = curr.substr(1, curr.length()-2);
        int ret = rewrite(curr, event);
        if(ret == 1) {
            return -1;
        } else if(ret == -1) {
            return 1;
        }
        return 0;
    } else if(op == 'U') {
        string top2 = operands.top();
        operands.pop();
        string top1 = operands.top();
        operands.pop();
        string curr = top2.substr(1, top2.length()-2);
        if(rewrite(curr, event) == 1)
            return 1;
        curr = top1.substr(1, top1.length()-2);
        cout<<"Checking for "<<curr<<"on event "<<event<<endl;
        if(rewrite(curr, event) != 0) {
            return -1;
        }
        top1.append(&op, 1);
        top1 += top2;
        next_stack.push(top1);
        return 0; 
    } else if(op == '|') {
        string top2 = operands.top();
        operands.pop();
        string top1 = operands.top();
        operands.pop();
        string curr2 = top2.substr(1, top2.length()-2);
        string curr1 = top1.substr(1, top1.length()-2);
        if(rewrite(curr1, event) == 1 || rewrite(curr2, event) == 1)
            return 1;
        if(rewrite(curr1, event) == 0 || rewrite(curr2, event) == 0)
            return 0;
        return -1;
    } else if(op == '&') {
        string top2 = operands.top();
        operands.pop();
        string top1 = operands.top();
        operands.pop();
        string curr2 = top2.substr(1, top2.length()-2);
        string curr1 = top1.substr(1, top1.length()-2);
        if(rewrite(curr1, event) == 1 && rewrite(curr2, event) == 1)
            return 1;
        if(rewrite(curr1, event) == -1 || rewrite(curr2, event) == -1)
            return -1;
        return 0;
    } else {
        if(operands.size() == 1) {
            string str = operands.top();
            if(str.length() == 1) {
                if (*(str.c_str()) == event || *(str.c_str()) == 'T')
                    return 1;
                else {
                    cout<<"Returning -1"<<endl;
                    return -1;
                }
            } else if(str[0] == '('){
                cout<<"operands: "<<str<<endl;
                str = str.substr(1, str.length()-2);
                return rewrite(str, event);
            } else
                return rewrite(str, event);
        }
    }

}
