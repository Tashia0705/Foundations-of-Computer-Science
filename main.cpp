#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <functional>

std::vector<int> lexi(std::vector<int> &alph, int N, std::vector<int> &result);

/*
 Task 4.
 Representing the set of states (and the set of accepting states) in a class using the
 constructor
*/
template<typename State>
class DFA {
  public:
    DFA(std::function<bool(State)> Qp, State q0p, std::function<State(State, int)> Dp,
        std::function<bool (State)> Fp): Q(Qp), q0(q0p), D(Dp), F(Fp) {};
    std::function<bool(State)> Q;
    State q0;
    std::function<State(State, int)> D;
    std::function<bool (State)> F;
    std::vector<State> traceStates;
    
    /*
     Task 10.
     Write a function that given a DFA and a string, determines if the string is accepted.
    */
    bool accepts(DFA d, std::vector<int> w) {
        State qi = q0;
        traceStates.clear();
        traceStates.push_back(qi);
        for(int i = 0; i < w.size(); i++) {
            qi = D(qi, w[i]);
            traceStates.push_back(qi);
        }
        
        if(F(qi))
            std::cout << "Accepted" << std::endl;
        else
            std::cout << "Denied" << std::endl;
        
        for(int i = 0; i < traceStates.size(); i++) // trace states
            std::cout << "-> " << traceStates[i] << " ";
        std::cout << std::endl;
        return F(qi);
    }
    
    
};

/*
 Task 7.
 DFA that accepts only strings of exactly that character
*/
DFA<int> task7(int ch) {
    DFA<int> *z = new DFA<int>(
        [](int x) { return (x == 0) || (x == 1) || (x == 2); },
        0,
        [=](int qi, int c) { if(c == ch && qi == 0) return 1; else return 2; },
        [](int qi) { return qi == 1; } );
    return *z;
}

int main(int argc, const char * argv[]) {
    /*
     Task 1.
     An alphabet is a finite set of numbers from 0 to some number N. I will use numbers 0 to 9.
     The characters will be individual elements from an alphabet... I will
     be using integers. ex. {0,1} is an alphabet
    */
    std::vector<int> set;
    for(int i = 0; i <= 9; i++) {
        set.push_back(i);
    }
    
    /*
     Task 2
     Strings are sequences of characters or "abstract elements drawn
     from an alphabet."
     ex. {1,0,1} is a sequence taken from the alphabet {0,1}
    */
    for(int j = 0; j < 30; j++) {
        std::vector<int> result;
        lexi(set, j, result);
    
        for(int i = 0; i < result.size(); i++)
            std::cout << result[i];
        std::cout << std::endl;
    }
    
    /*
     Task 5.
     DFA that accepts no string - has no accepting state
    */
    DFA<int> *x = new DFA<int>(
        [](int x) { return (x == 0); },
        0,
        [](int qi, int c) { return 0; },
        [](int qi) { return qi == 1; }
    );
    std::cout << x->D(0, 1) << std::endl;

    /*
     Task 6.
     DFA that accepts only empty string - accepting state is the start state and any other
     char passed will go to state 1 which is not an accepting state
    */
    DFA<int> *y = new DFA<int>(
        [](int x) { return (x == 0) || (x == 1); },
        1,
        [](int qi, int c) { return 1; },
        [](int qi) { return qi == 0; }
    );
    std::cout << y->D(0, 5) << std::endl;
    
    /*
     Task 8 - 12 different DFAs
    */
    // a. DFA that only accepts binary nums
    DFA<int> *binary = new DFA<int>(
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c){ if(c == 0 || c == 1) return 0; else return 1;},
        [](int qi) { return qi == 0; }
        );
    
    // b. DFA that only accepts even binary nums
    DFA<int> *evenBinary = new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if((c ^ 1) == c + 1) return 0; else return 1; },
        [](int qi) { return qi == 0; }
        );
    
    // c. DFA that only accepts odd binary nums
    DFA<int> *oddBinary = new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if((c ^ 1) == c + 1) return 1; else return 0; },
        [](int qi) { return qi == 0; }
        );
    
    // d. DFA that only accepts even numbers
    DFA<int> *evenNum = new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if (c % 2 != 0) return 1; else return 0;},
        [](int qi) { return qi == 0; }
        );
    
    // e. DFA that only accepts odd numbers
    DFA<int> *oddNum = new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if (c % 2 != 0) return 0; else return 1;},
        [](int qi) { return qi == 0; }
        );
    
    // f. DFA that only accepts numbers divisible by 6
    DFA<int> *sixDiv = new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if(c % 6 != 0) return 1; else return 0; },
        [](int qi) { return qi == 0; }
        );
    
    // g. DFA that only accepts evenly long strings
    DFA<int> *evenLength = new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if (qi == 1) return 1; else return 0;},
        [](int qi) { return qi == 0; }
        );
    
    // h. DFA that only accepts strings of odd lengths
    DFA<int> *oddLength = new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if (qi == 0) return 0; else return 1;},
        [](int qi) { return qi == 1; }
        );
    
    // i. DFA that only accepts strings made of 0s
    DFA<int> *zeros= new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if (c == 0) return 0; else return 1;},
        [](int qi) { return qi == 0; }
        );
    
    // j. DFA that only accepts strings made of 1s
    DFA<int> *ones= new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if (c == 1) return 0; else return 1;},
        [](int qi) { return qi == 0; }
        );
    
    // k. DFA that only accepts even number of 0s
    DFA<int> *evenZeros= new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if (c == 0 && qi != 1) return 0; else return 1;},
        [](int qi) { return qi == 0; }
        );
    
    // l. DFA that only accepts odd number of 1s
    DFA<int> *oddOnes= new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if (c == 1 && qi != 0) return 1; else return 0;},
        [](int qi) { return qi == 1; }
        );
    /*
     Task 9.
     For each example DFA, write a dozen tests of their behavior
    */
    std::cout << "DFA 1: Tesing rejected strings:" << std::endl;
    for(int i = 0; i < 6; i++)
        binary->accepts(*binary, {i,i+1,i+2});

    return 0;
}
    
/*
 Task 3.
 Function that generates the Nth string of a given alphabet’s lexicographic order
*/
std::vector<int> lexi(std::vector<int> &alph, int N, std::vector<int> &result) {
    if(N == 0) {
        std::cout << "";
    }
    else {
    
        // generate the value of the nth string
        unsigned long size = alph.size();
        int i = 0;
        int num = pow(size,i);
    
        while(N >= num) {
            N -= num;
            i++;
            num = pow(size, i);
        }
    
        // convert decimal to the right base system
        while(N > 0) {
            result.insert(result.begin(), N % size);
            N = N / size;
        }
        // adds 0s in the begining of string if needed
        if(result.size() < i) {
            for(int j = 0; j <= i - result.size(); j++) {
                result.insert(result.begin(), 0);
            }
        }
    }

    return result;
}

