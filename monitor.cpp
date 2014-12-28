#include "monitor.hpp"

using namespace std;

void Monitor::set_params(string form, int d) {
    this->formula = form;
    this->decision = d;
    current_stack.push(this->formula);
}

int Monitor::evaluate(char event) {
    while(!current_stack.empty()) {
        rewrite(current_stack.top());
        current_stack.pop();
    }
    swap(current_stack, next_stack);
    return 1;
}

int Monitor::reset(string formula) {
    return 1;
}

// return 0 if unstatisfied otherwise 1
int Monitor::rewrite(string current) {
    stack<char> bracs;
    char op;
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
            case 'X': op = current[i];
                      i++;
                      break;
            case '(': bracs.push('(');
                      curr = string(current[i]);
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
            default: operands.push(string(current[i]));
                     i++;

        };
    }
    if(op == 'G') {
        string top = operands.top();
        operands.pop();
        string curr = top.substr(1, curr.length()-1);
        if(rewrite(curr) == 1) {
            string next = string(op);
            next += top;
            next_stack.push(next);
            return 1;
        }
        return 0;
    } else if(op == 'F') {
        string top = operands.top();
        operands.pop();
        string curr = top.substr(1, curr.length()-1);
        if(rewrite(curr) == 0) {
            string next = string(op);
            next += top;
            next_stack.push(next);
        }
        return 1;
    } else if(op == 'X') {
        string next = operands.top();
        operands.pop();
        next = next.substr(1, curr.length()-1);
        next_stack.push(next);
        return 1;
    } else if(op == '~') {
        string curr = operands.top();
        operands.pop();
        curr = curr.substr(1, curr.length()-1);
        return rewrite(curr);
    } else if(op == 'U') {
        string top2 = operands.top();
        operands.pop();
        string top1 = operands.top();
        operands.pop();
        string curr = top2.substr(1, curr.length()-1);
        if(rewrite(curr) == 1)
            return 1;
        curr = top1.substr(1, curr.length()-1);
        if(rewrite(curr) == 0)
            return 0;
        top1 += string(op);
        top1 += top2;
        next_stack.push(top1);
        return 1; 
    } else if(op == '|') {
        string top2 = operands.top();
        operands.pop();
        string top1 = operands.top();
        operands.pop();
        string curr2 = top2.substr(1, curr.length()-1);
        string curr1 = top1.substr(1, curr.length()-1);
        if(rewrite(curr1) == 1 || rewrite(curr2) == 2)
            return 1;
        return 0;
    }
}
